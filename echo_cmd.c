/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:16:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/29 11:15:57 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_classic(int output, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(output, &str[i], 1);
		i++;
	}
}

int	cmd_echo(int output, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->option[1])
	{
		write(output, "\n", 1);
		return (0);
	}
	if (is_echo_n(cmd->option[1]))
		i++;
	while (cmd->option[i])
	{
		process_classic(output, cmd->option[i]);
		write(output, " ", 1);
		i++;
	}
	if (!is_echo_n(cmd->option[1]))
		write(output, "\n", 1);
	return (0);
}
