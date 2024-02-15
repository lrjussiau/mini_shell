/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 05:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/15 10:37:43 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//update the old pwd path
int	update_old_pwd(t_data **prompt)
{
	int		i;
	char	*old_path;
	char	*old;

	i = 0;
	if (update_old_pwd_or(prompt))
		return (-1);
	while ((*prompt)->env[i])
	{
		if (!ft_strncmp((*prompt)->env[i], "PWD=", 4))
		{
			old_path = (*prompt)->env[i];
			old = ft_conc("OLD", old_path);
			if (add_env_tab(prompt, old, 0))
				return (-1);
			free(old);
		}
		i++;
	}
	return (0);
}

//update the current pwd path
int	update_pwd(t_data **prompt)
{
	char	buf[150];
	int		i;

	i = 0;
	if (update_pwd_or(prompt))
		return (-1);
	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		while ((*prompt)->env[i])
		{
			if (!ft_strncmp((*prompt)->env[i], "PWD=", 4))
			{
				free((*prompt)->env[i]);
				(*prompt)->env[i] = ft_conc("PWD=", buf);
				return (0);
			}
			i++;
		}
		return (-1);
	}
	return (-1);
}

//execute pwd builtins 
//check how getpwd works if juste retrieve env variable
static int	cmd_pwd(int output)
{
	char	buf[500];

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		write(output, buf, ft_strlen(buf));
		write(output, "\n", 1);
		return (0);
	}
	else
	{
		printf("Error with pwd cmd");
		return (1);
	}
}

static int	cmd_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->option[1])
	{
		printf("exit\n");
		exit(1);
	}
	while (cmd->option[1][i])
	{
		if (!(cmd->option[1][i] >= 48 && cmd->option[1][i] <= 57))
		{
			printf("exit\nminishell: exit: %s", cmd->option[1]);
			printf(": numeric argument required\n");
			return (1);
		}
		i++;
	}
	if (cmd->option[2])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	printf("exit\n");
	exit(ft_atoi(cmd->option[1]));
}

//check if cmd is builtins, apply the desired cmd
int	check_builtins(int output, t_cmd *cmd, t_data **prompt)
{
	if (!ft_strncmp(cmd->name, "cd", 2) && ft_strlen(cmd->name) == 2)
		return (cmd_cd(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "pwd", 3) && ft_strlen(cmd->name) == 3)
		return (cmd_pwd(output));
	else if (!ft_strncmp(cmd->name, "echo", 4) && ft_strlen(cmd->name) == 4)
		return (cmd_echo(output, cmd));
	else if (!ft_strncmp(cmd->name, "export", 6) && ft_strlen(cmd->name) == 6)
		return (cmd_export(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "unset", 5) && ft_strlen(cmd->name) == 5)
		return (cmd_unset(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "env", 3) && ft_strlen(cmd->name) == 3)
		return (cmd_env(output, *prompt));
	else if (!ft_strncmp(cmd->name, "exit", 4) && ft_strlen(cmd->name) == 4)
		return (cmd_exit(cmd));
	else
		return (-2);
}
