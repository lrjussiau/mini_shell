/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:12:36 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/09 11:22:40 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*single_quote(char *str, int quote, t_data *data)
{
	char	*input;

	if (quote % 2 != 0)
	{
		while (1)
		{
			if (ft_strlcat(str, "\n", len(str) + 2) == 0)
				printf("ERROR : add n\n");
			input = readline("quote > ");
			if (ft_strlcat(str, input, len(str) + len(input) + 1) == 0)
				printf("ERROR : add input\n");
			if (ft_strncmp(input, "'", len(input)) == 0)
			{
				if (*input != 0)
				{
					free(input);
					break ;
				}
			}
			free(input);
		}
		free(data->str);
		data->str = ft_strdup(str);
	}
	return (str);
}

char	*double_quote(char *str, int quote, t_data *data)
{
	char	*input;

	if (quote % 2 != 0)
	{
		while (1)
		{
			if (ft_strlcat(str, "\n", len(str) + 2) == 0)
				printf("ERROR : add n\n");
			input = readline("dquote > ");
			if (ft_strlcat(str, input, len(str) + len(input) + 1) == 0)
				printf("ERROR : add input\n");
			if (ft_strncmp(input, "\"", len(input)) == 0)
			{
				if (*input != 0)
				{
					free(input);
					break ;
				}
			}
			free(input);
		}
		free(data->str);
		data->str = ft_strdup(str);
	}
	return (str);
}

void	check_quote(t_data *data)
{
	char	*tmp;
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	tmp = ft_strdup(data->str);
	if (tmp == NULL)
		error_handle(data, "malloc");
	while (tmp[i] != 0)
	{
		if (tmp[i++] == 39)
			quote++;
	}
	tmp = single_quote(tmp, quote, data);
	i = 0;
	quote = 0;
	while (tmp[i] != 0)
	{
		if (tmp[i++] == 34)
			quote++;
	}
	tmp = double_quote(tmp, quote, data);
	free(tmp);
}
