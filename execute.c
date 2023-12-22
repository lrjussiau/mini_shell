/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:04:59 by vvuadens          #+#    #+#             */
/*   Updated: 2023/12/20 10:30:58 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	open_fd(t_cmd *cmd, char c)
{
	int	fd;
	
	if (c == 'i')
	{
		
	}
	else
	{
		if (cmd->is_output_append)
		{
			fd = open()
		}
		else
		
	}
}

int	find_input(t_cmd *cmd)
{
	int	input;

	if (cmd->is_input_fd)
	{
		input = open_fd(cmd, i);
	}
	else if(cmd->is_input_limiter)
	{
		...
	}
	else
	{
		input = STDIN;
	}
}

int	find_output(t_cmd *cmd)
{
	int	output;

	if (cmd->is_output_fd)
	{
		output = open_fd(cmd, o);
	}
	else
	{
		output = STDOUT;
	}
}


void	apply_cmds(t_data prompt)
{
	t_cmd	*cmd;
	int		input;
	int		output;

	cmd = prompt.cmd;
	while (cmd)
	{
		input = find_input(cmd);
		output = find_output(cmd);
		execute_cmd(input, output, cmd);
		cmd = cm->next;
	}
}