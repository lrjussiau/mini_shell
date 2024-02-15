/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:16:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/15 10:16:51 by ljussiau         ###   ########.fr       */
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
	if (!data->str)
		return (1);
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
	while (str[i] == ' ' || str[i] == '\t')
		i++;
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
		if (g_heredoc_interrupted == 1)
		{
			// printf("okok\n");
			break ;
		}
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
	int		pipes[2];
	char	*buffer;

	pipe(pipes);
	buffer = malloc(10000);
	printf("pid before fork : %d\n", getpid());
	child = fork();
	if (child == 0)
	{
		run_signals(4);
		printf("pid before readline : %d\n", getpid());
		str = get_new_input(str, limiter);
		// printf("str : %s", str);
		// printf("heredoc child : %d\n", g_heredoc_interrupted);
		if (str)
		{
			write(pipes[1], str, ft_strlen(str));
		}
		close(pipes[0]); // Close the read-end of the pipe
		close(pipes[1]);
		exit(0);
	}
	else if (child > 0) {
		printf("pid before waitpid : %d\n", getpid());
		waitpid(child, &status, 0);
		printf("pid after waitpid : %d\n", getpid());
		// printf("heredoc : %d\n", g_heredoc_interrupted);
		if (read(pipes[0], buffer, 10000) != -1)
		{
			close(pipes[0]); // Close the read-end of the pipe
			close(pipes[1]); // Close the write-end of the pipe in the parent process
			return (NULL);
		}
	}
    else {
        exit(12);
    }
	if (buffer) {
        return (buffer);
    }
	return (NULL);
}

void	check_limiter(t_data *data)
{
	char	*limiter;

	if (ft_strnstr(data->str, "<<", ft_strlen(data->str)) != 0)
	{
		limiter = get_limiter(data->str);
		data->str = get_here_doc(data->str, limiter);
		// printf("str : %s\n", data->str);
		if (data->str == NULL)
			// printf("OK NORMAL\n");
		free(limiter);
	}
}
