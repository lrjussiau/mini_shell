/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 07:48:57 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/16 09:24:41 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//replace the value of the exported variable already existing
static	int	replace_env_value(char **env_tab, char *env_var, int n)
{
	int		i;
	int		le;
	int		mit;

	i = 0;
	if (ft_strchr(env_var, '=') == 0 && n == 1)
		return (0);
	le = ft_strlen(env_var) - ft_strlen(ft_strchr(env_var, '='));
	while (env_tab[i])
	{
		mit = miteux(env_tab[i], le);
		if ((!ft_strncmp(env_tab[i], env_var, le)) && (mit == le))
		{
			free(env_tab[i]);
			if (n == 0)
				env_tab[i] = ft_strdup(env_var);
			else
				env_tab[i] = add_quote(env_var);
			if (!env_tab[i])
				exit(1);
		}
		i++;
	}
	return (0);
}

//fill a new_tab with added element
static char	**fill_tab(char **env_var_tab, char *env_var, int n)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (env_var_tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (0);
	i = 0;
	while (env_var_tab[i])
	{
		new_tab[i] = ft_strdup(env_var_tab[i]);
		if (!new_tab[i])
			return (0);
		i++;
	}
	if (n == 0)
		new_tab[i] = ft_strdup(env_var);
	else
		new_tab[i] = add_quote(env_var);
	if (!new_tab[i])
		return (0);
	new_tab[i + 1] = 0;
	return (new_tab);
}

//alloc a new_tab with a new element
int	add_env_tab(t_data **prompt, char *env_var, int n)
{
	char	**env_var_tab;

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
		return (replace_env_value((*prompt)->origin, env_var, 1));
	}
	if (n == 0)
		(*prompt)->env = fill_tab(env_var_tab, env_var, n);
	else
		(*prompt)->origin = fill_tab(env_var_tab, env_var, n);
	if (!(*prompt)->env || !(*prompt)->origin)
		return (-2);
	ft_free_tab(env_var_tab);
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
		i++;
	new_tab = malloc(sizeof(char *) * i - 1);
	if (!new_tab)
		return (0);
	i = 0;
	while (env_var_tab[i])
	{
		if (ft_strncmp(env_var_tab[i], env_var, ft_strlen(env_var)))
		{
			new_tab[j] = ft_strdup(env_var_tab[i]);
			if (!new_tab[j++])
				return (0);
		}
		i++;
	}
	new_tab[j] = 0;
	return (new_tab);
}

//alloc a new_tab with a deleted element
int	del_env_tab(t_data **prompt, char *env_var, int n)
{
	int		j;
	char	**env_var_tab;
	char	**new_tab;

	j = 0;
	new_tab = 0;
	if (n == 1)
		env_var_tab = (*prompt)->env;
	else
		env_var_tab = (*prompt)->origin;
	if (!env_var_exist(env_var_tab, env_var))
		return (2);
	new_tab = delete_env(env_var_tab, env_var, new_tab);
	if (!new_tab)
	{
		perror("Malloc");
		exit (1);
	}
	ft_free_tab(env_var_tab);
	if (n == 1)
		(*prompt)->env = new_tab;
	else
		(*prompt)->origin = new_tab;
	return (1);
}
