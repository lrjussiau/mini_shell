/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:21:10 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/20 11:26:57 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	get_nb_output(char **strs)
{
	int	i;
	int	nb_output;

	i = 0;
	nb_output = 0;
	while (strs[i] != NULL)
	{
		if (ft_strnstr(strs[i], ">>", ft_strlen(strs[i])) != 0)
			nb_output++;
		else if (ft_strnstr(strs[i], ">", ft_strlen(strs[i])) != 0)
			nb_output++;
		i++;
	}
	return (nb_output);
}

char	**add_strs(char **strs, char *str, int nb)
{
	int	i;

	if (strs == NULL)
		strs = (char **)malloc(sizeof(char *) * (nb + 1));
	i = 0;
	while (strs[i] != NULL)
		i++;
	strs[i] = ft_strdup(str);
	i++;
	strs[i] = NULL;
	return (strs);
}