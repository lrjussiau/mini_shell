/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 07:48:57 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/09 10:18:11 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//check the structure of env var "[char] '=' [char]" for export
int	check_env_var(char	*var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != ' ')
	{
		if (var[i] == '=')
		{
			while (var[i] && var[i] != ' ')
				i++;
			if (valid_var(var) != 2)
				return (-1);
			return (0);
		}
		i++;
	}	
	return (-1);
}

//check if env var name exist
int	env_var_exist(char **env_var_tab, char *env_var)
{
	int		i;
	size_t	len;

	i = 0;
	while (env_var_tab[i])
	{
		len = env_var_tab[i] - ft_strchr(env_var_tab[i], '=');
		if (!ft_strncmp(env_var_tab[i], env_var, len))
			return (1);
		i++;
	}
	return (0);
}

//check if env_var name char are in [a-b][A-B][_]->for unset && for export
int	valid_var(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=' && env_var[i])
	{
		if (!(env_var[i] <= 90 && env_var[i] >= 65
				|| env_var[i] >= 97 && env_var[i] <= 122 || env_var[i] == 95))
			return (0);
		i++;
	}
	if (env_var[i] == '=' && i != 0)
		return (2);
	return (1);
}

//replace the value of the exported variable already existing
int	replace_env_value(t_data **prompt, char **env_var_tab, char *env_var)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (env_var_tab[i])
		i++;
	new_tab = ft_malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env_var_tab[i])
	{
		if (ft_strncmp(env_var_tab[i], env_var, env_var - ft_strchr(env_var, '=')))
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
	new_tab[i] = '\0';
	ft_free_tab(env_var_tab);
	(*prompt)->env_var = new_tab;
}

//alloc a new_tab with a new element
int	add_env_tab(t_data **prompt, char *env_var)
{
	int		i;
	char	**new_tab;
	char	**env_var_tab;

	i = 0;
	env_var_tab = (*prompt)->env_var;
	if (!env_var_exist(env_var_tab, env_var))
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
	new_tab[i] = ft_strdup(env_var_tab[i]);
	if (!new_tab[i])
		perror("MALLOC");
	new_tab[i + 1] = '\0';
	//new_tab = fill_tab(new_tab, prompt, env_var);
	ft_free_tab(env_var_tab);
	(*prompt)->env_var = new_tab;
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
	env_var_tab = (*prompt)->env_var;
	if (!env_var_exist(env_var_tab, env_var))
		return (0);
	while (env_var_tab[i])
		i++;
	new_tab = ft_malloc(sizeof(char *) * i);
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
	new_tab[j] = '\0';
	ft_free_tab(env_var_tab);
	(*prompt)->env_var = new_tab;
	return (0);
}

//fill a new_tab with a new element
/*char	**fill_tab(char **new_tab, t_data **prompt, char *env_var)
{
	int		i;
	int		j;
	char	**env_var_tab;

	i = 0;
	env_var_tab = prompt->env_var;
	while (env_var_tab[i])
	{
		j = 0;
		while (env_var_tab[i][j])
		{
			new_tab[i][j] == env_var_tab[i][j];
			j++;
		}
		new_tab[i][j] = '\0';
		i++;
	}
	new_tab[i] = env_var;
	new_tab[i + 1] = '\0';
	return (new_tab);
}*/

//fill a new_tab with a deleted element (env_var)
/*char	**reduce_tab(char **new_tab, t_data **prompt, char *env_var)
{
	int		i;
	int		j;
	int		k;
	char	**env_var_tab;

	i = 0;
	k = 0;
	env_var_tab = prompt->env_var;
	while (env_var_tab[i])
	{
		j = 0;
		if (ft_strncmp(env_var_tab[i], env_var, ft_strlen(env_var)))
		{
			while (env_var_tab[i][j])
			{
				new_tab[k][j] == env_var_tab[i][j];
				j++;
			}
			new_tab[i][j] = '\0';
			k++;
		}
		i++;
	}
	new_tab[k] = '\0';
	return (new_tab);
}*/