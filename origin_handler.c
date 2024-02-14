/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   origin_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:57:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/13 06:02:39 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
		if (str[i] == '=')
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
