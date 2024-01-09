/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 08:13:11 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/09 10:04:58 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	error_handle(t_data *data, char *error)
{
	if (ft_strncmp(error, "malloc", len(error)) == 0)
	{
		ft_free_input(data);
		perror("Malloc Error.");
	}
}

void	ft_free_inout(t_cmd *cmd)
{
	t_inout	*inout;
	t_inout	*tmp_inout;

	inout = cmd->input;
	while (inout != NULL)
	{
		tmp_inout = inout;
		inout = inout->next;
		free(tmp_inout->name);
		free(tmp_inout);
	}
	inout = cmd->output;
	while (inout != NULL)
	{
		tmp_inout = inout;
		inout = inout->next;
		free(tmp_inout->name);
		free(tmp_inout);
	}
}

void	ft_free_input(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*tmp_cmd;

	free(data->str);
	cmd = data->cmd;
	while (cmd != NULL)
	{
		if (cmd->option != NULL)
			ft_free_tab(cmd->option);
		free(cmd->name);
		ft_free_inout(cmd);
		tmp_cmd = cmd;
		cmd = cmd->next;
		free(tmp_cmd);
	}
	free(data);
}

void	ft_free_env(t_data *data)
{
	ft_free_tab(data->env);
	ft_free_tab(data->origin);
}
