/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 07:48:57 by vvuadens          #+#    #+#             */
/*   Updated: 2023/12/28 11:48:18 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//check the structure of env var "[char] '=' [char]"
//add valid_var() ->check the char more thoroughly 
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
			return (0);
		}
		i++;
	}
	return (-1);
}

//fill a new_tab with a new element
char	**fill_tab(char **new_tab, t_data **prompt, char *env_var)
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
}

//alloc a new_tab with a new element
int	add_env_tab(t_data **prompt, char *env_var)
{
	int		i;
	int		j;
	char	**new_tab;
	char	**env_var_tab;

	i = 0;
	j = 0;
	env_var_tab = (*prompt)->env_var;
	while (env_var_tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 2);
	if (!new_tab)
		return (-1);
	i = 0;
	while (env_var_tab[i])
	{
		j = 0;
		while (env_var_tab[i][j])
			j++;
		new_tab[i] = malloc(sizeof(char) * j + 1);
		if (!new_tab[i])
		{
			free(new_tab);
			return (-1);
		}
		i++;
	}
	new_tab[i] = malloc(sizeof(char) * ft_strlen(env_tab) + 1);
	if (!new_tab[i])
	{
		free(new_tab);
		return (-1);
	}
	new_tab = fill_tab(new_tab, prompt, env_var);
	ft_free_tab(env_var_tab);
	(*prompt)->env_var = new_tab;
	return (0);
}

int	env_var_exist(char **env_var_tab, char *env_var)
{
	int	i;

	i = 0;
	while (env_var_tab[i])
	{
		if (!ft_strncmp(env_var_tab[i], env_var, ft_strlen(env_var)))
			return (1);
		i++;
	}
	return (0);
}

//fill a new_tab with a deleted element (env_var)
char	**reduce_tab(char **new_tab, t_data **prompt, char *env_var)
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
}

//alloc a new_tab with a deleted element
int	del_env_tab(t_data **prompt, char *env_var)
{
	int		i;
	int		j;
	char	**env_var_tab;
	char	**new_tab;

	i = 0;
	env_var_tab = (*prompt)->env_var;
	if (!env_var_exist(env_var_tab, env_var))
		return (0);
	while (env_var_tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * i);
	if (!new_tab)
		return (-1);
	i = 0;
	while (env_var_tab[i])
	{
		j = 0;
		if (ft_strncmp(env_var_tab[i], env_var, ft_strlen(env_var)))
		{
			while (env_var_tab[i][j])
				j++;
			new_tab[i] = malloc(sizeof(char) * j + 1);
			if (!new_tab[i])
			{
				free(new_tab);
				return (-1);
			}
		}
		i++;
	}
	new_tab = reduce_tab(new_tab, prompt, env_var);
	ft_free_tab(env_var_tab);
	(*prompt)->env_var = new_tab;
	return (0);
}

//check if env_var name char are in [a-b][A-B][_]
int	valid_var(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		if (!(env_var[i] <= 90 && env_var[i] >= 65
				|| env_var[i] >= 97 && env_var[i] <= 122 || env_var[i] == 95))
			return (0);
		i++;
	}
	return (1);
}

//execute env -l "cmd"
int	cmd_env_l(t_cmd *cmd, t_data **prompt)
{
	
}

//execute env [env_var] [cmd]
int	cmd_env_v(t_cmd *cmd)
{
	
}

//check what typ of env cmd to execute
int	exec_env_cmd(t_cmd	*cmd, t_data **prompt)
{
	if (cmd->option[0] == "-l")
	{
		if (!cmd_env_l(cmd, prompt))
			return (0);
		else
		{
			perror("Error executing env -l cmd");
			return (-1);
		}
	}
	else
	{
		if (!cmd_env_v(cmd))
			return (0);
		else
		{
			perror("Error executing env cmd");
			return (-1);
		}
	}
}


