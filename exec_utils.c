/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:30:02 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/18 09:58:01 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fd_error(int input, int output)
{
	if (input == -1 || output == -1)
	{
		printf("Error opening file");
		//ft_clean();
		exit (-1);
	}
}

char	*ft_conc(char *str, char *input)
{
	char	*ret_str;
	int		i;
	int		j;

	ret_str = malloc((ft_strlen(str) + ft_strlen(input) + 1) * sizeof(char));
	if (!ret_str)
	{
		printf("Malloc error");
		exit(-1);
	}
	i = 0;
	while (str[i])
	{
		ret_str[i] = str[i];
		i++;
	}
	j = 0;
	while (input[j])
	{
		ret_str[i + j] = input[j];
		j++;
	}
	ret_str[i + j] = '\0';
	return (ret_str);
}

char	*cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*paths;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			paths = envp[i] + 5;
		i++;
	}
	if (ft_strchr(cmd, '/'))
		path = find_exec_path(cmd, envp, paths);
	else
		path = find_path(cmd, paths);
	if (!path)
		return (0);
		//exit(1);
	return (path);
}