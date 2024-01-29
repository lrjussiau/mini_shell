/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 05:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/29 19:02:33 by vvuadens         ###   ########.fr       */
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
	char	buf[150];

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

static int	cmd_exit(void)
{
	exit(0);
}

//check if cmd is builtins, apply the desired cmd
int	check_builtins(int output, t_cmd *cmd, t_data **prompt)
{
	if (!ft_strncmp(cmd->name, "cd", ft_strlen(cmd->name)))
		return (cmd_cd(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "pwd", ft_strlen(cmd->name)))
		return (cmd_pwd(output));
	else if (!ft_strncmp(cmd->name, "echo", ft_strlen(cmd->name)))
		return (cmd_echo(output, cmd));
	else if (!ft_strncmp(cmd->name, "export", ft_strlen(cmd->name)))
		return (cmd_export(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "unset", ft_strlen(cmd->name)))
		return (cmd_unset(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "env", ft_strlen(cmd->name)))
		return (cmd_env(output, *prompt));
	else if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name)))
		return (cmd_exit());
	else
		return (-2);
}
