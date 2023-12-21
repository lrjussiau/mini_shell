/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:23:06 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/21 10:27:00 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->nb_pipe = 0;
	data->str = NULL;
	data->last_status = 0;
	data->is_env = false;
	data->cmd = init_cmd();
	return (data);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*command;

	command = (t_cmd *)malloc(sizeof(t_cmd));
	if (command == NULL)
		return (NULL);
	command->name = NULL;
	command->option = NULL;
	command->next = NULL;
	command->is_pipe = false;
	command->input = init_inout();
	command->output = init_inout();
	return (command);
}

t_inout	*init_inout(void)
{
	t_inout	*init;

	init = (t_inout *)malloc(sizeof(t_inout));
	if (init == NULL)
		return (NULL);
	init->is_append = false;
	init->is_fd = false;
	init->is_limiter = false;
	init->name = NULL;
	init->next = NULL;
	return (init);
}
