/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:16:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/24 11:37:51 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	checker(t_data *data)
{
	char	*str;
	int		i;
	int		nb_limiter;

	i = 0;
	nb_limiter = 0;
	str = data->str;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			nb_limiter++;
		i++;
	}
	if (nb_limiter > 1)
	{
		printf("You can not put more than one limiter\n");
		return (1);
	}
	check_quote(data);
	check_limiter(data);
	return (0);
}

int	len_limiter(char *str)
{
	int	i;
	int	start;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i - start);
}

char	*get_limiter(char *str)
{
	char	*limiter;
	int		i;
	int		len;
	int		j;

	i = 0;
	while (str[i] == '<' && str[i + 1] == '<')
		i += 2;
	len = len_limiter(str + i);
	limiter = (char *)malloc(sizeof(char) * (len + 1));
	if (!limiter)
		return (NULL);
	j = 0;
	while (j < len)
	{
		limiter[j] = str[i + j];
		j++;
	}
	limiter[j] = '\0';
	return (limiter);
}

char	*get_new_input(char	*str, char *limiter)
{
	char	*input;
	char	*tmp;

	while (1)
	{
		input = readline("heredoc > ");
		tmp = str;
		str = ft_append_str(str, input);
		free(tmp);
		if ((ft_strncmp(input, limiter, ft_strlen(input)) == 0))
		{
			free(input);
			break ;
		}
		free(input);
	}
	return (str);
}

void	check_limiter(t_data *data)
{
	char	*limiter;

	if (ft_strnstr(data->str, "<<", ft_strlen(data->str)) != 0)
	{
		limiter = get_limiter(data->str);
		data->str = get_new_input(data->str, limiter);
		free(limiter);
	}
}
