/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:24:59 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/19 15:17:30 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	limiter_input(char *limiter, char *prompt)
{
	char	*str;
	int		input_fd;
	char	*after_lim;

	input_fd = open("limiter_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd_error(input_fd, 0);
	str = ft_strchr(prompt, '\n');
	after_lim = ft_strnstr(str, limiter, ft_strlen(str));
	write(input_fd, str + 1, ((ft_strlen(str + 1) - ft_strlen(after_lim)) - 1));
	close(input_fd);
	input_fd = open("limiter_file", O_RDONLY);
	fd_error(input_fd, 0);
	return (input_fd);
}

int	find_input(t_cmd *cmd, int **fd_tab, int *k, char *str)
{
	int		input;
	t_inout	*inp;

	inp = cmd->input;
	if (inp->name)
	{
		while (inp->next->next)
			inp = inp->next;
		if (inp->is_fd)
		{
			input = open(inp->name, O_RDONLY);
		}
		else
		{
			input = limiter_input(inp->name, str);
		}
	}
	else if (*k != 0)
		input = fd_tab[*k][0];
	else
		input = STDIN_FILENO;
	fd_error(input, 0);
	return (input);
}

static int	output_file(t_inout *out, t_cmd *cmd)
{
	int	output;

	while (out->next->next)
	{
		output = open(out->name, O_TRUNC | O_CREAT, 0644);
		close(output);
		out = out->next;
	}
	if (out->is_append || !ft_strncmp(cmd->option[0], "echo", 5))
		output = open(out->name, O_WRONLY | O_APPEND | O_CREAT);
	else
		output = open(out->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (output);
}

int	find_output(t_cmd *cmd, int **fd_tab, int *k)
{
	int		output;
	t_inout	*out;

	out = cmd->output;
	if (out->name)
	{
		output = output_file(out, cmd);
	}
	else if (cmd->is_pipe)
	{
		cmd = cmd->next;
		if (!(cmd->input->name))
		{
			output = fd_tab[*k + 1][1];
			(*k)++;
		}
		else
			output = STDOUT_FILENO;
	}
	else
		output = STDOUT_FILENO;
	fd_error(0, output);
	return (output);
}
