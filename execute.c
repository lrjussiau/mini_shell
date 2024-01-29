/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:57:23 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/29 14:56:26 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	free_fdtab(int **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	while (len >= 0)
	{
		free(tab[len]);
		len--;
	}
	free(tab);
}

static int	execute_cmd( int input, int output, t_cmd *cmd, char **envp)
{
	pid_t	child;
	int		child_status;

	child = fork();
	run_signals(2);
	if (child == 0)
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		execve(cmd_path(cmd->name, envp), cmd->option, envp);
		printf("minishell: %s: command not found\n", cmd->name);
		exit(EXIT_FAILURE);
	}
	else if (child > 0)
	{
		if (input != 0)
			close(input);
		if (output != 1)
			close(output);
		waitpid(child, &child_status, 0);
		return (child_status);
	}
	else
		exit(EXIT_FAILURE);
}

//printf("cmd_info: in: %d, out: %d, cmd: %s\n", in,out, cmd->name);
static void	execute(int in, int out, t_cmd *cmd, t_data **prompt)
{
	int	status;
	int	input_error;

	input_error = fd_error(in);
	if (!input_error)
		status = check_builtins(out, cmd, prompt);
	else
		status = input_error;
	if (status == -2)
	{
		status = execute_cmd(in, out, cmd, (*prompt)->env);
		if (status == 256)
			status = 127;
		if (status == 2)
			status = 130;
	}
	(*prompt)->last_status = status;
}

int	apply_cmds(t_data *prompt)
{
	t_cmd	*cmd;
	int		input;
	int		output;
	int		**fd_tab;
	int		*k;

	k = &(int){0};
	fd_tab = 0;
	cmd = prompt->cmd;
	fd_tab = create_fd_tab(find_pipe_nb(prompt), fd_tab);
	while (cmd->next)
	{
		input = find_input(cmd, fd_tab, k, prompt->str);
		output = find_output(cmd, fd_tab, k);
		execute(input, output, cmd, &prompt);
		if (output != 1)
			close(output);
		if (open("limiter_file", O_RDONLY) != -1)
			unlink("limiter_file");
		cmd = cmd->next;
	}
	free_fdtab(fd_tab);
	return (prompt->last_status);
}
