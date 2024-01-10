/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:16:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/10 08:18:53 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*append_str(char *str, char *input)
{
	
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
	// int		len;

	while (1)
	{
		input = readline("heredoc > ");
		printf("input : %s\n", input);
		printf("limiter : %s\n", limiter);
		printf("result : %d\n", ft_strncmp(input, limiter, ft_strlen(limiter)));
		// ft_strlcat(str, "\n", ft_strlen(str) + 2);
		// len = ft_strlen(str) + ft_strlen(input) + 1;
		// ft_strlcat(str, input, len);
		if ((ft_strncmp(input, limiter, ft_strlen(limiter)) == 0))
		{
			printf("After compare\n");
			printf("input : %s\n", input);
			printf("limiter : %s\n", limiter);
			break ;
		}
		free(input);
	}
	printf("sortie\n");
	printf("input : %s\n", input);
	printf("limiter : %s\n", limiter);
	free(input);
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
