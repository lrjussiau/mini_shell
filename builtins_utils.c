/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 07:48:57 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/29 18:51:45 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static	char	*add_quote(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!new_str)
		exit(1);
	while (i < ft_strlen(str))
	{
		if (str[i] == '=' || str[i + 1] == 0)
		{
			new_str[j] = str[i];
			j++;
			new_str[j] = '"';
		}
		else
			new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = 0;
	//free(str);
	return (new_str);
}

//replace the value of the exported variable already existing
static	int	replace_env_value(char **env_tab, char *env_var, int n)
{
	int		i;
	char	**tab;
	int		len;

	i = 0;
	tab = env_tab;
	len = ft_strlen(env_var) - ft_strlen(ft_strchr(env_var, '='));
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], env_var, len))
		{
			free(tab[i]);
			if (n == 0)
				tab[i] = ft_strdup(env_var);
			else
				tab[i] = add_quote(env_var);
			if (!tab[i])
			{
				perror("MALLOC");
				exit(1);
			}
		}
		i++;
	}
	return (0);
}

//fill a new_tab with added element
static char	**fill_tab(char **new_tab, char **env_var_tab, char *env_var, int n)
{
	int	i;

	i = 0;
	while (env_var_tab[i])
	{
		new_tab[i] = ft_strdup(env_var_tab[i]);
		if (!new_tab[i])
		{
			perror("MALLOC");
			exit(1);
		}
		i++;
	}
	if (n == 0)
		new_tab[i] = ft_strdup(env_var);
	else
		new_tab[i] = add_quote(env_var);
	if (!new_tab[i])
	{
		perror("MALLOC");
		exit(1);
	}
	new_tab[i + 1] = 0;
	return (new_tab);
}

//alloc a new_tab with a new element
int	add_env_tab(t_data **prompt, char *env_var, int n)
{
	int		i;
	char	**new_tab;
	char	**env_var_tab;

	i = 0;
	if (n == 0)
		env_var_tab = (*prompt)->env;
	else
		env_var_tab = (*prompt)->origin;
	if (env_var_exist(env_var_tab, env_var))
	{
		if (n == 0)
		{
			replace_env_value((*prompt)->origin, env_var, 1);
			return (replace_env_value((*prompt)->env, env_var, 0));
		}
		else
			replace_env_value((*prompt)->origin, env_var, 1);
	}
	while (env_var_tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (-1);
	new_tab = fill_tab(new_tab, env_var_tab, env_var, n);
	if (!new_tab)
		return (-1);
	ft_free_tab(env_var_tab);
	if (n == 0)
		(*prompt)->env = new_tab;
	else
		(*prompt)->origin = new_tab;
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
				exit(1);
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
		return (2);
	while (env_var_tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * i - 1);
	if (!new_tab)
		return (0);
	new_tab = delete_env(env_var_tab, env_var, new_tab);
	if (!new_tab)
		return (0);
	ft_free_tab(env_var_tab);
	(*prompt)->env = new_tab;
	return (1);
}
