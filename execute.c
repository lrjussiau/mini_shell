/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:57:23 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/17 06:42:22 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

static int execute_cmd( int input, int output, t_cmd *cmd, int **fd_tab, char **envp)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		ft_close(fd_tab);
		return (execve(cmd_path(cmd->name, envp), cmd->option, envp));
	}
	else if (child > 0)
	{
		wait(&child);
		return (0);
	}
	else
	{
		//free_tab((void **)fd_tab);
		//perror(strerror(errno));
		exit(EXIT_FAILURE);
		return (-1);
	}
}

//check if cmd is builtins, execute the command, update last status
static void	execute(int in, int out, t_cmd *cmd, t_data **prompt, int **fd_tab)
{
	int	status;

	status = check_builtins(out, cmd, prompt);
	if (status == -2)
	{
		status = execute_cmd(in, out, cmd, fd_tab, (*prompt)->env);
		if (status == -1)
			status = 127;
	}
	else
		printf("\nis_builtins\n");
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
		fd_error(input, output);
		execute(input, output, cmd, &prompt, fd_tab);
		if (output != 1)
			close(output);
		if (input != 0)
			close(input);
		if (open("limiter_file", O_RDONLY) != -1)
			unlink("limiter_file");
		cmd = cmd->next;
	}
	return (prompt->last_status);
}