/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:57:23 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/19 14:39:27 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

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

/*if (input != 0)
		dup2(input, STDIN_FILENO);
if (output != 1)
	dup2(output, STDOUT_FILENO);*/
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
		if (input != 0)
			close(input);
		if (output != 1)
			close(output);
		execve(cmd_path(cmd->name, envp), cmd->option, envp);
		exit(EXIT_FAILURE);
	}
	else if (child > 0)
	{
		waitpid(child, &child_status, 0);
		if (child_status == 0)
			return (0);
		return (-1);
	}
	else
		exit(EXIT_FAILURE);
}

//printf("cmd_info: in: %d, out: %d, cmd: %s\n", in,out, cmd->name);
//check if cmd is builtins, execute the command, update last status
//certain commands need \n others don't cat/ls
//makefile compilation cmd appear
//ctrl c sometimes doesn't work, ^\ in blocking case should exit
//? This global variable cannot provide any other information or data access than the number of a received signal
//echo "cat lol.c | cat > lol.c" doesn't work
//cat | cat | ls oui et non
static void	execute(int in, int out, t_cmd *cmd, t_data **prompt)
{
	int	status;

	status = check_builtins(out, cmd, prompt);
	if (status == -2)
	{
		status = execute_cmd(in, out, cmd, (*prompt)->env);
		if (status == -1)
		{
			printf("minishell: %s: command not found\n", cmd->name);
			status = 127;
		}
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
	cmd = prompt->cmd;
	fd_tab = create_fd_tab(find_pipe_nb(prompt), &fd_tab);
	while (cmd->next)
	{
		input = find_input(cmd, fd_tab, k, prompt->str);
		output = find_output(cmd, fd_tab, k);
		fd_error(input, output);
		execute(input, output, cmd, &prompt);
		if (output != 1)
			close(output);
		if (input != 0)
			close(input);
		if (open("limiter_file", O_RDONLY) != -1)
			unlink("limiter_file");
		cmd = cmd->next;
	}
	free_fdtab(fd_tab);
	return (prompt->last_status);
}
