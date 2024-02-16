/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   origin_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:57:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/16 08:30:03 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	ft_strl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

char	*add_quote(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (ft_strchr(str, '=') == 0)
		return (ft_strdup(str));
	new_str = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!new_str)
		exit(1);
	while (i < ft_strlen(str))
	{
		new_str[j] = str[i];
		j++;
		if ((str[i] == '=') && (i == ft_strl(str)))
			new_str[j++] = '"';
		i++;
	}
	new_str[j++] = '"';
	new_str[j] = 0;
	return (new_str);
}

char	**ft_copy_or(char	**strs)
{
	char	**tab;
	int		i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	tab = malloc((i + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (strs[i] != NULL)
	{
		tab[i] = add_quote(strs[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	update_old_pwd_or(t_data **prompt)
{
	int		i;
	char	*old_path;
	char	*old;

	i = 0;
	while ((*prompt)->origin[i])
	{
		if (!ft_strncmp((*prompt)->origin[i], "PWD=", 4))
		{
			old_path = (*prompt)->origin[i];
			old = ft_conc("OLD", old_path);
			if (add_env_tab(prompt, old, 1))
				return (-1);
			free(old);
		}
		i++;
	}
	return (0);
}

//update the current pwd path
int	update_pwd_or(t_data **prompt)
{
	char	buf[200];
	int		i;
	char	*new;

	i = 0;
	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		while ((*prompt)->origin[i])
		{
			if (!ft_strncmp((*prompt)->origin[i], "PWD=", 4))
			{
				free((*prompt)->origin[i]);
				new = ft_conc("PWD=", buf);
				(*prompt)->origin[i] = add_quote(new);
				free(new);
				return (0);
			}
			i++;
		}
		return (-1);
	}
	return (-1);
}
