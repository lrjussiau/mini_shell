/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:58:02 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/21 10:38:43 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	get_cmd(char **strs, int i, t_cmd *cmd)
{
	cmd->name = ft_strdup(strs[i]);
	i++;
	if (!is_inout(strs[i]))
	{
		cmd->option = ft_strdup(strs[i]);
		return (1);
	}
	return (0);
}
