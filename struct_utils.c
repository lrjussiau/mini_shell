/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:23:06 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/20 09:09:57 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_data	*init_data(t_data *data)
{
	t_cmd	*command;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data -> nb_pipe = 0;
	data -> str = NULL;
	data -> last_status = 0;
	data -> is_env = false;
	command = init_cmd(command);
	data -> cmd = command;
	return (data);
}

t_cmd	*init_cmd(t_cmd *command)
{
	command = (t_cmd *)malloc(sizeof(t_cmd));
	if (command == NULL)
		return (NULL);
	command -> cmd = NULL;
	command -> option = NULL;
	command -> is_output_fd = false;
	command -> is_output_append = false;
	command -> output_fd = NULL;
	command -> is_input_fd = false;
	command -> is_input_limiter = false;
	command -> input_fd = NULL;
	command -> input_limiter = NULL;
	command -> next = NULL;
	command -> is_pipe = false;
	return (command);
}
