/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:30:02 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/12 08:33:16 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	fd_error(int input)
{
	if (input == -1)
	{
		printf("No such file or directory\n");
		return (1);
	}
	return (0);
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
	return (path);
}

char	*find_old(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD=", 7))
			return (envp[i] + 7);
		i++;
	}
	return (0);
}

int	is_echo_n(char *cmd_option)
{
	if (ft_strlen(cmd_option) == 2 && cmd_option[0] == '-'
		&& cmd_option[1] == 'n')
		return (1);
	return (0);
}
