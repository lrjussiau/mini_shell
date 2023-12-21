/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:51:04 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/21 10:41:42 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	is_inout(char *str)
{
	if (str == NULL)
		return (true);
	if (ft_strnstr(str, ">>", ft_strlen(str)) != 0)
		return (true);
	else if (ft_strnstr(str, ">", ft_strlen(str)) != 0)
		return (true);
	if (ft_strnstr(str, "<<", ft_strlen(str)) != 0)
		return (true);
	else if (ft_strnstr(str, "<<", ft_strlen(str)) != 0)
		return (true);
	return (false);
}

int	len(const char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

void	print_data(t_data *data)
{
	int 	i;
	t_cmd	*current;
	t_inout	*input;
	t_inout *output;

	i = 0;
	printf("-----------\n");
	printf("Data Store\n-----------\n\nNb Pipe : %d\nStr input : %s\n", data->nb_pipe, data->str);
	printf("Int Last status : %d\n\n", data->last_status);
	current = data->cmd;
	while (current -> next != NULL)
	{
		input = current->input;
		output = current->output;
		printf("-----------\n");
		printf("Command %d\n", i);
		printf("-----------\n");
		printf("Command : %s\n", current->name);
		printf("Option : %s\n", current->option);
		printf("Is there a pipe after : %s\n", current->is_pipe ? "true" : "false");
		while (output -> next != NULL)
		{
			printf("output : %s\n", output->name);
			printf("\tIs it fd : %s\n", output->is_fd ? "true" : "false");
			printf("\tIs it append : %s\n", output->is_append ? "true" : "false");
			printf("\tIs it limiter : %s\n", output->is_limiter ? "true" : "false");
			output = output->next;
		}
		current = current->next;
		i++;
	}
}