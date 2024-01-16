/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:14:49 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/16 09:50:32 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	cmd_exp_p(int output, t_data *prompt)
{
	int	i;

	i = 0;
	while (prompt->env[i])
	{
		write(output, "export ", 7);
		write(output, prompt->env[i], ft_strlen(prompt->env[i]));
		write(output, "\n", 1);
		i++;
	}
	return (0);
}

//execute export builtins
int	cmd_export(int output, t_cmd *cmd, t_data **prompt)
{
	int	i;

	i = 1;
	if (!cmd->option[1])
		return (cmd_exp_p(output, *prompt));
	while (cmd->option[i])
	{
		printf("time\n");
		if (!check_env_var(cmd->option[i]))
		{
			if (add_env_tab(prompt, cmd->option[i]))
			{
				perror("Error updating env_tab");
				if (!cmd->option[i + 1])
					return (-1);
			}
		}
		else
		{
			perror("Not a valid identifier");
			if (!cmd->option[i + 1])
				return (-1);
		}
		i++;
	}
	return (0);
}

//execute unset builtins
int	cmd_unset(t_cmd *cmd, t_data **prompt)
{
	int	i;

	i = 1;
	while (cmd->option[i])
	{
		if (valid_var(cmd->option[i]) == 1)
		{
			if (del_env_tab(prompt, cmd->option[i]))
			{
				perror("Error unset cmd");
				if (!cmd->option[i + 1])
					return (-1);
			}
			else
			{
				perror("Not a valid identifier");
				if (!cmd->option[i + 1])
					return (-1);
			}
			i++;
		}
		else
		{
			perror("Not a valid identifier");
			if (!cmd->option[i + 1])
				return (-1);
		}
	}
	return (0);
}

//execute env builtins & update $?
int	cmd_env(int output, t_data *prompt)
{
	int	i;

	i = 0;
	while (prompt->env[i])
	{
		write(output, prompt->env[i], ft_strlen(prompt->env[i]));
		write(output, "\n", 1);
		i++;
	}
	return (0);
}
