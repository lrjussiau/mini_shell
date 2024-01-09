/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:16:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/09 09:16:41 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
	char	*tmp;
	char	*input;

	while (*str != '\n' && *str != '\0')
		str++;
	tmp = ft_strdup(str);
	while (1)
	{
		if (ft_strlcat(tmp, "\n", len(tmp) + 2) == 0)
			printf("ERROR : add n\n");
		input = readline("heredoc > ");
		if (ft_strlcat(tmp, input, len(tmp) + len(input) + 1) == 0)
			printf("ERROR : add input\n");
		if (ft_strncmp(input, limiter, ft_strlen(input)) == 0)
			break ;
		free(input);
	}
	free(input);
	return (tmp);
}

void	check_limiter(t_data *data)
{
	char	*limiter;
	char	*tmp;
	int		len;

	if (ft_strnstr(data->str, "<<", ft_strlen(data->str)) != 0)
	{
		limiter = get_limiter(data->str);
		tmp = get_new_input(data->str, limiter);
		len = ft_strlen(data->str) + ft_strlen(tmp) + 1;
		if (ft_strlcat(data->str, tmp, len) == 0)
			printf("ERROR FINAL\n");
		free(tmp);
		free(limiter);
	}
}
