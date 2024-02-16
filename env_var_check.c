/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:08:03 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/16 09:54:08 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*ft_getenv(char *str, t_data *data)
{
	char	*ret_str;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], str, ft_strlen(str)) != 0)
		{
			ret_str = ft_strchr(data->env[i], '=') + 1;
			return (ret_str);
		}
		i++;
	}
	return (NULL);
}

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

int	check_env_var(char	*var, t_data **prompt)
{
	int	i;

	i = 0;
	if (valid_var(var) == 2)
	{
		if (valid_val(ft_strchr(var, '=') + 1))
		{
			add_env_tab(prompt, var, 1);
			return (add_env_tab(prompt, var, 0));
		}
		return (-1);
	}
	else if (valid_var(var) == 1)
		return (add_env_tab(prompt, var, 1));
	return (-1);
}

//len = ft_strlen(env_tab[i]) - ft_strlen(ft_strchr(env_tab[i], '='));
//check if env var name exist
int	env_var_exist(char **tab, char *env_var)
{
	int		i;
	size_t	len_1;
	size_t	len_2;

	i = 0;
	if (!(ft_strchr(env_var, '=')))
		len_1 = ft_strlen(env_var);
	else
		len_1 = ft_strlen(env_var) - ft_strlen(ft_strchr(env_var, '='));
	while (tab[i])
	{
		if (!(ft_strchr(tab[i], '=')))
			len_2 = ft_strlen(tab[i]);
		else
			len_2 = ft_strlen(tab[i]) - ft_strlen(ft_strchr(tab[i], '='));
		if (!ft_strncmp(tab[i], env_var, len_2) && len_1 == len_2)
			return (1);
		i++;
	}
	return (0);
}

//check if env_var name char are in [a-b][A-B][_][0-9]
//(sauf si premier char)->for unset && for export
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
	if (env_var[i] == '=' && i == 0)
		return (42);
	return (1);
}
