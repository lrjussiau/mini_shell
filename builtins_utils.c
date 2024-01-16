/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 07:48:57 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/16 09:47:52 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//replace the value of the exported variable already existing
//todo->simplify it
int	replace_env_value(t_data **prompt, char **env_var_tab, char *env_var)
{
	int		i;
	int		len;
	char	**new_tab;

	i = 0;
	len = ft_strlen(env_var) - ft_strlen(ft_strchr(env_var, '='));
	while (env_var_tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env_var_tab[i])
	{
		if (!ft_strncmp(env_var_tab[i], env_var, len))
		{
			new_tab[i] = ft_strdup(env_var);
			if (!new_tab[i])
				perror("MALLOC");
		}
		else
		{
			new_tab[i] = ft_strdup(env_var_tab[i]);
			if (!new_tab[i])
				perror("MALLOC");
		}
		i++;
	}
	new_tab[i] = 0;
	//ft_free_tab(env_var_tab);
	(*prompt)->env = new_tab;
	printf("env[0]: %s\n", (*prompt)->env[0]);
	return (0);
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
		return (replace_env_value(prompt, env_var_tab, env_var));
	while (env_var_tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (env_var_tab[i])
	{
		new_tab[i] = ft_strdup(env_var_tab[i]);
		if (!new_tab[i])
			perror("MALLOC");
		i++;
	}
	new_tab[i] = ft_strdup(env_var);
	if (!new_tab[i])
		perror("MALLOC");
	new_tab[i + 1] = 0;
	//new_tab = fill_tab(new_tab, prompt, env_var);
	//ft_free_tab(env_var_tab);
	(*prompt)->env= new_tab;
	return (0);
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
	new_tab = malloc(sizeof(char *) * i);
	i = 0;
	while (env_var_tab[i])
	{
		if (ft_strncmp(env_var_tab[i], env_var, ft_strlen(env_var)))
		{
			new_tab[j] = ft_strdup(env_var_tab[i]);
			if (!new_tab[j++])
				perror("MALLOC");
		}
		i++;
	}
	new_tab[j] = 0;
	ft_free_tab(env_var_tab);
	(*prompt)->env = new_tab;
	return (1);
}
