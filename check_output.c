/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:59:22 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/21 09:08:14 by ljussiau         ###   ########.fr       */
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
		return (1);
	}
	else
	{
		strs[i] += 2;
		current->name = ft_strdup(strs[i]);
		current->is_append = true;
		append_output(cmd);
		current = current->next;
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
		return (1);
	}
	else
	{
		strs[i]++;
		current->name = ft_strdup(strs[i]);
		current->is_fd = true;
		append_output(cmd);
		current = current->next;
		return (0);
	}
}

int	check_output(char **strs, int i, t_cmd *cmd)
{
	if (ft_strnstr(strs[i], ">>", ft_strlen(strs[i])) != 0)
		return (get_fd_append(strs, i, cmd));
	else if (ft_strnstr(strs[i], ">", ft_strlen(strs[i])) != 0)
		return (get_fd_output(strs, i, cmd));
	return (0);
}
