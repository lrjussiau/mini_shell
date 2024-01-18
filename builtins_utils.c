/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 07:48:57 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/18 08:27:00 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_free_ta(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("free: %s\n", tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
}

//replace the value of the exported variable already existing
static	int	replace_env_value(t_data **prompt, char *env_var)
{
	int		i;
	char	**tab;
	int		len;

	i = 0;
	tab = (*prompt)->env;
	len = ft_strlen(env_var) - ft_strlen(ft_strchr(env_var, '='));
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], env_var, len))
		{
			free(tab[i]);
			tab[i] = ft_strdup(env_var);
			if (!tab[i])
			{
				perror("MALLOC");
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

//fill a new_tab with added element
static char	**fill_tab(char **new_tab, char **env_var_tab, char *env_var)
{
	int	i;

	i = 0;
	while (env_var_tab[i])
	{
		new_tab[i] = ft_strdup(env_var_tab[i]);
		if (!new_tab[i])
		{
			perror("MALLOC");
			return (0);
		}
		i++;
	}
	new_tab[i] = ft_strdup(env_var);
	if (!new_tab[i])
	{
		perror("MALLOC");
		return (0);
	}
	new_tab[i + 1] = 0;
	return (new_tab);
}

//alloc a new_tab with a new element
int	add_env_tab(t_data **prompt, char *env_var)
{
	int		i;
	char	**new_tab;
	char	**env_var_tab;

	i = 0;
	env_var_tab = (*prompt)->env;
	if (env_var_exist(env_var_tab, env_var))
		return (replace_env_value(prompt, env_var));
	while (env_var_tab[i])
		i++;
	printf("i: %d\n", i);
	new_tab = malloc(sizeof(char *) * i + 1);
	if (!new_tab)
		return (-1);
	new_tab = fill_tab(new_tab, env_var_tab, env_var);
	if (!new_tab)
		return (-1);
	ft_free_ta(env_var_tab);
	(*prompt)->env = new_tab;
	return (0);
}

//fill a new tab with deleted element
static char	**delete_env(char **env_var_tab, char *env_var, char **new_tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_var_tab[i])
	{
		if (ft_strncmp(env_var_tab[i], env_var, ft_strlen(env_var)))
		{
			new_tab[j] = ft_strdup(env_var_tab[i]);
			if (!new_tab[j++])
			{
				perror("MALLOC");
				return (0);
			}
		}
		i++;
	}
	new_tab[j] = 0;
	return (new_tab);
}

//alloc a new_tab with a deleted element
int	del_env_tab(t_data **prompt, char *env_var)
{
	int		i;
	int		j;
	char	**env_var_tab;
	char	**new_tab;

	i = 0;
	j = 0;
	env_var_tab = (*prompt)->env;
	if (!env_var_exist(env_var_tab, env_var))
		return (0);
	while (env_var_tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * i - 1);
	if (!new_tab)
		return (0);
	new_tab = delete_env(env_var_tab, env_var, new_tab);
	if (!new_tab)
		return (0);
	ft_free_ta(env_var_tab);
	(*prompt)->env = new_tab;
	return (1);
}
