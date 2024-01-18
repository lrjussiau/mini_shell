/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:12:36 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/17 10:45:03 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	single_quote(char *str, int quote, t_data *data)
{
	char	*input;
	char	*tmp;

	if (quote % 2 != 0)
	{
		while (1)
		{
			input = readline("quote > ");
			tmp = str;
			str = ft_append_str(str, input);
			free(tmp);
			if (ft_strncmp(input, "'", 1) == 0)
			{
				free(input);
				break ;
			}
			free(input);
		}
		data->str = ft_strdup(str);
		free(str);
	}
}

void	double_quote(char *str, int quote, t_data *data)
{
	char	*input;
	char	*tmp;

	if (quote % 2 != 0)
	{
		while (1)
		{
			input = readline("dquote > ");
			tmp = str;
			str = ft_append_str(str, input);
			free(tmp);
			if (ft_strncmp(input, "\"", 1) == 0)
			{
				free(input);
				break ;
			}
			free(input);
		}
		data->str = ft_strdup(str);
		free(str);
	}
}

void	check_quote(t_data *data)
{
	char	*tmp;
	int		i;
	int		quote;
	int		dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	tmp = ft_strdup(data->str);
	if (tmp == NULL)
		error_handle(data, "malloc");
	while (tmp[i] != 0)
	{
		if ((tmp[i] == '\'') && dquote % 2 == 0)
			quote++;
		if ((tmp[i] == '"') && quote % 2 == 0)
			dquote++;
		i++;
	}
	single_quote(data->str, quote, data);
	double_quote(data->str, dquote, data);
	free(tmp);
}
