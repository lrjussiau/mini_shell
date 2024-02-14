/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:14:49 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/13 06:57:38 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*clean_opt(char *str, int i, int j)
{
	char	*new_str;

	while (str[i])
		if (str[i] == 39 || str[i++] == 34)
			j++;
	if (j != 0)
	{
		i = 0;
		new_str = malloc(sizeof(char) * ft_strlen(str) - j + 1);
		if (!new_str)
			exit(1);
		j = 0;
		while (str[i])
		{
			if (str[i] == 39 || str[i] == 34)
				i++;
			else
				new_str[j++] = str[i++];
		}
		new_str[j] = 0;
		return (new_str);
	}
	else
		return (str);
}

static int	cmd_exp_p(int output, t_data *prompt)
{
	int	i;

	i = 0;
	while (prompt->origin[i])
	{
		write(output, "declare -x ", 11);
		write(output, prompt->origin[i], ft_strlen(prompt->origin[i]));
		write(output, "\n", 1);
		i++;
	}
	return (0);
}

//execute export builtins
int	cmd_export(int output, t_cmd *cmd, t_data **prompt)
{
	int	i;
	int	err;

	i = 1;
	if (!cmd->option[1])
		return (cmd_exp_p(output, *prompt));
	while (cmd->option[i])
	{
		err = check_env_var(clean_opt(cmd->option[i], 0, 0), prompt);
		if (err == -1)
		{
			printf("minishell: export: %s: not a valid id\n", cmd->option[i]);
			if (!cmd->option[i + 1])
				return (1);
		}
		else if (err == -2)
		{
			perror("Malloc");
			exit(1);
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
		if (valid_var(cmd->option[i]) != 1)
		{
			printf("minishel: unset: %s: not a valid id\n", cmd->option[i]);
			if (!cmd->option[i + 1])
				return (1);
		}
		else if (del_env_tab(prompt, cmd->option[i], 0) == 2)
		{
			if (!cmd->option[i + 1])
				return (1);
		}
		else
			del_env_tab(prompt, cmd->option[i], 1);
		i++;
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
