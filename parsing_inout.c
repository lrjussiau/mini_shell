/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_inout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:59:22 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/03 08:11:33 by ljussiau         ###   ########.fr       */
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
		ft_strcat(strs[i], strs[i + 1]);
		ft_bzero (strs[i + 1], ft_strlen(strs[i + 1]));
	}
	strs[i] += 2;
	current->name = ft_strdup(strs[i]);
	current->is_append = true;
	append_output(cmd);
	current = current->next;
	strs[i] -= 2;
	return (0);
}

int	get_fd_output(char **strs, int i, t_cmd *cmd)
{
	t_inout	*current;

	current = cmd->output;
	while (current->next != NULL)
		current = current->next;
	if (ft_strlen (strs[i]) == 1)
	{
		ft_strcat(strs[i], strs[i + 1]);
		ft_bzero (strs[i + 1], ft_strlen(strs[i + 1]));
	}
	strs[i]++;
	current->name = ft_strdup(strs[i]);
	current->is_fd = true;
	append_output(cmd);
	current = current->next;
	strs[i]--;
	return (0);
}
