/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:08:03 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/18 08:27:28 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//check if env_value is ascii writable
static int	valid_val(char *val)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (!(val[i] >= 21 && val[i] <= 126))
			return (0);
		i++;
	}
	return (1);
}

int	check_env_var(char	*var)
{
	int	i;

	i = 0;
	if (valid_var(var) == 2)
	{
		printf("here\n");
		if (valid_val(ft_strchr(var, '=') + 1))
			return (0);
		return (-1);
	}
	printf("num: %d\n", valid_var(var));
	return(-1);
	/*while (var[i] && var[i] != ' ')
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
	return (-1);*/
}

//check if env var name exist
int	env_var_exist(char **env_var_tab, char *env_var)
{
	int		i;
	size_t	len;

	i = 0;
	while (env_var_tab[i])
	{
		printf("env: %s\n", env_var_tab[i]);
		len = ft_strlen(env_var_tab[i]) - ft_strlen(ft_strchr(env_var_tab[i], '='));
		/*if (ft_strchr(env_var, '='))
			len = ft_strlen(env_var) - ft_strlen(ft_strchr(env_var, '='));
		else*/
		if (!ft_strncmp(env_var_tab[i], env_var, len))
			return (1);
		i++;
	}
	return (0);
}

//check if env_var name char are in [a-b][A-B][_][0-9](sauf si premier char)->for unset && for export
int	valid_var(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=' && env_var[i])
	{
		if (!((env_var[i] <= 90 && env_var[i] >= 65)
				|| (env_var[i] >= 97 && env_var[i] <= 122) || env_var[i] == 95
				|| (env_var[i] >= 48 && env_var[i] <= 57)))
			return (0);
		if (i == 0 && (env_var[i] >= 48 && env_var[i] <= 57))
			return (0);
		i++;
	}
	if (env_var[i] == '=' && i != 0)
		return (2);
	return (1);
}