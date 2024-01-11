/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:58:02 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/11 08:35:17 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	get_cmd(char **strs, int i, t_cmd *cmd)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	cmd->name = ft_strdup(strs[i]);
	while (strs[i] != NULL)
	{
		i++;
		if (is_inout(strs[i]))
			break ;
		j++;
	}
	i -= j + 1;
	cmd->option = (char **)malloc(sizeof(char *) * (j + 2));
	while (k <= j)
	{
		cmd->option[k] = ft_strdup(strs[i]);
		i++;
		k++;
	}
	cmd->option[k] = NULL;
	return (j);
}
