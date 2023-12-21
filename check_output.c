/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:59:22 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/21 07:32:40 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	get_fd_append(char **strs, int i, t_data *data)
{
	if (ft_strlen (strs[i]) == 2)
	{
		data->cmd->output->name = ft_strdup(strs[i + 1]);
		data->cmd->output->is_append = true;
		return (1);
	}
	else
	{
		strs[i] += 2;
		data->cmd->output->name = ft_strdup(strs[i]);
		data->cmd->output->is_append = true;
		return (0);
	}
}

int	get_fd_output(char **strs, int i, t_data *data)
{
	if (ft_strlen (strs[i]) == 1)
	{
		data->cmd->output->name = ft_strdup(strs[i + 1]);
		data->cmd->output->is_fd = true;
		return (1);
	}
	else
	{
		strs[i]++;
		data->cmd->output->name = ft_strdup(strs[i]);
		data->cmd->output->is_fd = true;
		return (0);
	}
}

int	check_output(char **strs, int i, t_data *data)
{
	if (ft_strnstr(strs[i], ">>", ft_strlen(strs[i])) != 0)
		return (get_fd_append(strs, i, data));
	else if (ft_strnstr(strs[i], ">", ft_strlen(strs[i])) != 0)
		return (get_fd_output(strs, i, data));
	return (0);
}
