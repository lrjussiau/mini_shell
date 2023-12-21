/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_inout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:59:22 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/21 10:23:58 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	get_fd_append(char **strs, int i, t_cmd *cmd)
{
	t_inout	*current;

	current = cmd->output;
	while (current->next != NULL)
		current = current->next;
	if (ft_strlen (strs[i]) == 2)
	{
		current->name = ft_strdup(strs[i + 1]);
		current->is_append = true;
		append_output(cmd);
		current = current->next;
		ft_strlcat(strs[i], strs[i + 1], len(strs[i]) + len(strs[i + 1] + 1));
		return (1);
	}
	else
	{
		strs[i] += 2;
		current->name = ft_strdup(strs[i]);
		current->is_append = true;
		append_output(cmd);
		current = current->next;
		strs[i] -= 2;
		return (0);
	}
}

int	get_fd_output(char **strs, int i, t_cmd *cmd)
{
	t_inout	*current;

	current = cmd->output;
	while (current->next != NULL)
		current = current->next;
	if (ft_strlen (strs[i]) == 1)
	{
		current->name = ft_strdup(strs[i + 1]);
		current->is_fd = true;
		append_output(cmd);
		current = current->next;
		ft_strlcat(strs[i], strs[i + 1], len(strs[i]) + len(strs[i + 1] + 1));
		return (1);
	}
	else
	{
		strs[i]++;
		current->name = ft_strdup(strs[i]);
		current->is_fd = true;
		append_output(cmd);
		current = current->next;
		strs[i]--;
		return (0);
	}
}
