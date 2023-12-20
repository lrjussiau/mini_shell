/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:23:06 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/20 11:12:03 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_data	*init_data(void)
{
	t_data	*data;
	t_cmd	*cmd;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data -> nb_pipe = 0;
	data -> str = NULL;
	data -> last_status = 0;
	data -> is_env = false;
	data -> cmd = NULL;
	cmd = init_cmd();
	append_cmd(data, cmd);
	return (data);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*command;
	char	**output_fd;

	command = (t_cmd *)malloc(sizeof(t_cmd));
	if (command == NULL)
		return (NULL);
	command -> cmd = NULL;
	command -> option = NULL;
	command -> is_output_fd = false;
	command -> is_output_append = false;
	command -> nb_output = 0;
	command -> output_fd = NULL;
	command -> is_input_fd = false;
	command -> is_input_limiter = false;
	command -> input_fd = NULL;
	command -> input_limiter = NULL;
	command -> next = NULL;
	command -> is_pipe = false;
	return (command);
}

void	append_cmd(t_data *data, t_cmd *new_cmd)
{
	t_cmd	*tmp;

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

void	print_char_array(char **array)
{
	int	i;

	if (array == NULL)
	{
		printf("\tNULL.\n");
		return ;
	}
	i = 0;
	while (array[i] != NULL)
	{
		printf("\t%s\n", array[i]);
		i++;
	}
}

void	print_data(t_data *data)
{
	int		i;
	t_cmd	*current;

	i = 0;
	printf("Data Store\nNb Pipe : %d\nStr input : %s\n", data->nb_pipe, data->str);
	printf("Int Last status : %d\n\n", data->last_status);
	current = data->cmd;
	while (current->next != NULL)
	{
		printf("-----------\n");
		printf("Command %d\n", i);
		printf("-----------\n");
		printf("is_output_fd: %s\n", current->is_output_fd ? "true" : "false");
		printf("is_output_append: %s\n", current->is_output_append ? "true" : "false");
		printf("output_fd : \n");
		print_char_array(current->output_fd);
		printf("is_input_fd: %s\n", current->is_input_fd ? "true" : "false");
		printf("is_input_limiter: %s\n", current->is_input_limiter? "true" : "false");

		printf("is_pipe: %s\n", current->is_pipe ? "true" : "false");
		current = current->next;
		i++;
	}
}
