/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:57:23 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/29 14:04:16 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Mini Shell > cat | cat
cmd_info: in: 0, out: 13, cmd: (null)
Segmentation fault: 11*/
//Try ctrl-\ after running a blocking command like cat without arguments or grep “something“
//Try a command like : echo "cat lol.c | cat > lol.c"
//echo '$USER' must print "$USER".

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
/*if (input != 0)
	close(input);
if (output != 1)
	close(output);*/
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
		//printf("child: %d\n", child_status);
		return (child_status);
	}
	else
		exit(EXIT_FAILURE);
}

//printf("cmd_info: in: %d, out: %d, cmd: %s\n", in,out, cmd->name);

// the number of a received signal
//echo "cat lol.c | cat > lol.c" doesn't work
static void	execute(int in, int out, t_cmd *cmd, t_data **prompt)
{
	int	status;
	int	input_error;

	//printf("cmd_info: in: %d, out: %d, cmd: %s\n", in,out, cmd->name);
	input_error = fd_error(in);
	if (!input_error)
		status = check_builtins(out, cmd, prompt);
	else
		status = input_error;
	if (status == -2)
	{
		status = execute_cmd(in, out, cmd, (*prompt)->env);
		if (status == 256)
		{
			//printf("minishell: %s: command not found\n", cmd->name);
			status = 127;
		}
		if (status == 2)
			status = 130;
	}
	(*prompt)->last_status = status;
}
//if (input != 0)
// 	close(input);
//printf_fdtab(fd_tab);

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
	//printf_fdtab(fd_tab);
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
	//ft_close(fd_tab);
	free_fdtab(fd_tab);
	return (prompt->last_status);
}
