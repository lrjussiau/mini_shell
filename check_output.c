/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:59:22 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/20 08:48:08 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	get_fd_append(char **strs, int i, t_data *data)
{
	if (ft_strlen (strs[i]) == 2)
	{
		printf("Output append on this fd : %s\n", strs[i + 1]);
		data -> cmd -> is_output_append = true;
		return (1);
	}
	else
	{
		strs[i] += 2;
		printf("Output append on this fd : %s\n", strs[i]);
		data -> cmd -> is_output_append = true;
		return (0);
	}
}

int	get_fd_output(char **strs, int i, t_data *data)
{
	if (ft_strlen (strs[i]) == 1)
	{
		printf("Output on this fd : %s\n", strs[i + 1]);
		data -> cmd -> is_output_fd = true;
		return (1);
	}
	else
	{
		strs[i]++;
		printf("Output on this fd : %s\n", strs[i]);
		data -> cmd -> is_output_fd = true;
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
