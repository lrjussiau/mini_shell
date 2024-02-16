/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:16:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/16 10:33:47 by ljussiau         ###   ########.fr       */
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
		printf("minishell: more than one limiter\n");
		return (1);
	}
	check_quote(data);
	check_limiter(data);
	if (!data->str)
		return (1);
	return (0);
}

char	*get_new_input(char	*str, char *limiter)
{
	char	*input;
	char	*tmp;

	while (1)
	{
		run_signals(4);
		input = readline("heredoc > ");
		if (!input)
			exit(0);
		tmp = str;
		str = ft_append_str(str, input);
		free(tmp);
		if ((ft_strncmp(input, limiter, ft_strlen(input)) == 0))
		{
			if (input[0] != '\0')
			{
				free(input);
				break ;
			}
		}
		free(input);
	}
	return (str);
}

char	*get_here_doc(char *str, char *limiter)
{
	pid_t	child;
	int		status;
	char	*buffer;
	int		fd;

	buffer = malloc(10000);
	fd = open("tmp", O_CREAT | O_WRONLY, 0777);
	child = fork();
	if (child == 0)
	{
		str = get_new_input(str, limiter);
		write(fd, str, ft_strlen(str));
		exit(0);
	}
	else if (child > 0)
	{
		waitpid(child, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (NULL);
		close(fd);
		fd = open("tmp", O_RDONLY);
		read(fd, buffer, 10000);
		unlink("tmp");
	}
	return (buffer);
}

void	check_limiter(t_data *data)
{
	char	*limiter;

	if (ft_strnstr(data->str, "<<", ft_strlen(data->str)) != 0)
	{
		limiter = get_limiter(data->str);
		data->str = get_here_doc(data->str, limiter);
		if (data->str && data->str[0] == '\0')
			data->str = NULL;
		free(limiter);
	}
}
