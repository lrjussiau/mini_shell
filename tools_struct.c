/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:21:10 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/16 07:24:24 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	append_cmd(t_data *data)
{
	t_cmd	*new_cmd;
	t_cmd	*tmp;

	new_cmd = init_cmd();
	if (data == NULL || new_cmd == NULL)
		return ;
	if (data->cmd == NULL)
	{
		data->cmd = new_cmd;
		return ;
	}
	tmp = data->cmd;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

void	append_input(t_cmd *cmd)
{
	t_inout	*tmp;
	t_inout	*new_cmd;

	new_cmd = init_inout();
	if (cmd == NULL || new_cmd == NULL)
		return ;
	if (cmd->input == NULL)
	{
		cmd->input = new_cmd;
		return ;
	}
	tmp = cmd->input;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

void	append_output(t_cmd *cmd)
{
	t_inout	*tmp;
	t_inout	*new_cmd;

	new_cmd = init_inout();
	if (cmd == NULL || new_cmd == NULL)
		return ;
	if (cmd->output == NULL)
	{
		cmd->output = new_cmd;
		return ;
	}
	tmp = cmd->output;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_cmd;
}
