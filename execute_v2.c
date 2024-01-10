/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:57:23 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/10 07:00:19 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//gestion du tmp_input dans le cas ou ils sont deux->tab comme dans pipex?

void	ft_close(int **fd_tab)
{
	int	i;

	i = 0;
	while (fd_tab[i])
	{
		close(fd_tab[i][0]);
		close(fd_tab[i][1]);
		i++;
	}
}

static void	execute_cmd( int input, int output, t_data *cmd, char **envp, int **fd_tab)
{
	pid_t	child;
	char	**args;

	child = fork();
	if (child == 0)
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		ft_close(fd_tab);
		execve(cmd->name, cmd->option, envp);
	}
	else if (child > 0)
		return ;
	else
	{
		free(arr);
		free_tab((void **)fd_tab);
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int	find_input_v2(t_cmd **cmd, t_data *prompt, int **fd_tab, int *k)
{
	int		input;
	t_inout	*input;

	input = (*cmd)->input;
	if (input)
	{
		while (input->next)
			input = input->next;
		if (input->is_fd)
		{
			input = open((*cmd)->name, O_RDONLY);
		}
		//input->is_limiter ! creation limiter file
		else
		{
			input = open("limiter_file", O_RDWR | O_CREAT, 0644);
			fd_error(input, 0);
			copy_limiter_str(input, prompt);
		}
	}
	//input given
	else
		input = fd_tab[*k][0];
	return (input);
}

int	find_output_v2(t_cmd **cmd, t_data *prompt, int **fd_tab, int *k)
{
	int		output;
	t_inout	*output;

	output = (*cmd)->output;
	if (output)
	{
		while (output->next)
			output = output->next;
		if (output->is_append)
			output = open(output->name, O_WRONLY | O_APPEND);
		else
			output = open(output->name, O_WRONLY | O_CREAT, 0644);
	}
	else if ((*cmd)->is_pipe)
	{
		if (!(*cmd)->next->inputs)
		{
			output = fd_tab[*k + 1][1];
			(*k)++;
		}
		//?
		else
			output = STDOUT_FILENO;
	}
	else
		output = STDOUT_FILENO;
}

//check if cmd is builtins, execute the command, update last status
void	execute(int input int output, t_cmd *cmd, t_data **prompt, int **fd_tab)
{
	int	status;

	status = check_builtins(output, cmd, prompt);
	if (status == -2)
		(*prompt)->last_status = execute_cmd(input, output, cmd, fd_tab, (*prompt)->env);
	else
		(*prompt)->last_status = status;
}

int	**create_fd_tab(int pipe_nbr)
{
	int	**fd_tab;
	int	i;

	i = 0;
	fd_tab = malloc(sizeof (int *) * (pipe_nbr));
	if (!fd_tab)
		return (0);
	while (pipe_nbr - 1)
	{
		fd_tab[i] = malloc(sizeof(int) * 2);
		if (!fd_tab[i])
		{
			free_tab((void **)fd_tab);
			return (0);
		}
		if (pipe(fd_tab[i++]) == -1)
		{
			free_tab((void **)fd_tab);
			return (0);
		}
		pipe_nbr--;
	}
	fd_tab[i] = 0;
	return (0);
}

int	find_pipe_nb(t_data *prompt)
{
	t_cmd	*cmd;
	int		i;

	cmd = prompt->cmd;
	i = 0;
	while (cmd->next)
	{
		if (!cmd->next->inputs && !cmd->output)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	apply_cmds_v2(t_data *prompt)
{
	t_cmd	*cmd;
	int		input;
	int		output;
	int		**fd_tab;
	int		*k;

	k = &(int){0};
	cmd = prompt->cmd;
	fd_tab = create_fd_tab(find_pipe_nb(prompt));
	while (cmd)
	{
		input = find_input_v2(&cmd, prompt);
		output = find_output_v2(&cmd, &prompt)
		fd_error(input, output);
		execute(input, output, cmd, prompt, fd_tab);
		close(output);
		close(input);
		cmd = cmd->next;
	}
}