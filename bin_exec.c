/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:28:18 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/19 11:25:36 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*find_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", ft_strlen("PWD=")))
			return (ft_strchr(envp[i], '/'));
		i++;
	}
	return (0);
}

char	*find_exec_path(char *cmd, char **envp, char *paths)
{
	char	*path;

	if (cmd[0] == '.' && cmd[1] == '/')
	{
		if (ft_strchr(cmd + 2, '/'))
		{
			return (cmd);
		}
		else
		{
			path = find_path(cmd, paths);
			if (!path)
				path = find_pwd(envp);
			return (ft_conc(path, cmd + 1));
		}
	}
	else
		return (cmd);
}

//free_tab((void **)tab);
char	*find_path(char *cmd, char *paths)
{
	char	**tab;
	char	*path;
	char	*path2;
	int		i;

	i = 0;
	tab = ft_split(paths, ':');
	if (!tab)
		return (0);
	while (tab[i])
	{
		path = ft_strjoin(tab[i++], "/");
		path2 = ft_strjoin(path, cmd);
		free(path);
		if (access(path2, X_OK) != -1)
		{
			free(cmd);
			return (path2);
		}
		free(path2);
	}
	free(cmd);
	return (0);
}
