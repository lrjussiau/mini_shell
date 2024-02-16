/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:51:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/16 10:31:35 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	is_inout(char *str)
{
	if (str == NULL)
		return (true);
	if (ft_strnstr(str, ">>", ft_strlen(">>")) != 0)
		return (true);
	else if (ft_strnstr(str, ">", ft_strlen(">")) != 0)
		return (true);
	if (ft_strnstr(str, "<", ft_strlen("<")) != 0)
		return (true);
	else if (ft_strnstr(str, "<<", ft_strlen("<<")) != 0)
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

char	*ft_strcat(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

int	get_nb_str(char **strs)
{
	int	n;

	n = 0;
	while (strs[n] != NULL)
		n++;
	return (n);
}

char	**ft_copy_tab(char	**strs)
{
	char	**tab;
	int		nb_str;
	int		i;

	nb_str = get_nb_str(strs);
	tab = malloc((nb_str + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (strs[i] != NULL)
	{
		tab[i] = ft_strdup(strs[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

// void	print_data(t_data *data)
// {
// 	int 	i;
// 	int		j;
// 	t_cmd	*current;
// 	t_inout	*input;
// 	t_inout *output;

// 	i = 0;
// 	printf("\n-----------\n");
// 	printf("Data Store\n-----------\n\nNb Pipe : %d\n Str
//  input : %s\n", data->nb_pipe, data->str);
// 	printf("Last status : %d\n\n", data->last_status);
// 	current = data->cmd;
// 	while (current -> next != NULL)
// 	{
// 		j = 0;
// 		input = current->input;
// 		output = current->output;
// 		printf("-----------\n");
// 		printf("Command %d\n", i);
// 		printf("-----------\n");
// 		printf("Command : %s\n", current->name);
// 		if (current->option != NULL)
// 		{
// 			while (current->option[j] != NULL)
// 			{
// 				printf("\tOption %d : %s\n", j+1, current->option[j]);
// 				j++;
// 			}
// 		}
// 	printf("Is there a pipe after : %s\n", current->is_pipe ? "true" : "false");
// 		while (input -> next != NULL)
// 		{
// 			printf("input : %s\n", input->name);
// 			printf("\tIs it fd : %s\n", input->is_fd ? "true" : "false");
// 			printf("\tIs it append : %s\n", input->is_append ? "true" : "false");
// 		printf("\tIs it limiter : %s\n", input->is_limiter ? "true" : "false");
// 			input = input->next;
// 		}
// 		while (output -> next != NULL)
// 		{
// 			printf("output : %s\n", output->name);
// 			printf("\tIs it fd : %s\n", output->is_fd ? "true" : "false");
// 			printf("\tIs it append : %s\n", output->is_append ? "true" : "false");
// 		printf("\tIs it limiter : %s\n", output->is_limiter ? "true" : "false");
// 			output = output->next;
// 		}
// 		current = current->next;
// 		i++;
// 	}
// 	printf("\n");
// }