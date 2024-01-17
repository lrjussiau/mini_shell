/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 05:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/17 06:25:26 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*     todo          */

//last_status
//prompt with nothing

#include <stdio.h>
#include "mini_shell.h"

//update the old pwd path
static int	update_old_pwd(t_data **prompt)
{
	int		i;
	char	*old_path;

	i = 0;
	while ((*prompt)->env[i])
	{
		if (!ft_strncmp((*prompt)->env[i], "PWD=", 4))
			old_path = (*prompt)->env[i];
		if (!ft_strncmp((*prompt)->env[i], "OLDPWD=", 7))
		{
			//free((*prompt)->env[i]);
			(*prompt)->env[i] = ft_conc("OLD", old_path);
			return (0);	
		}
		i++;
	}
	if (add_env_tab(prompt, ft_conc("OLD", old_path)))
		return (-1);
	return (0);
}

//update the current pwd path
static int	update_pwd(t_data **prompt)
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

//execute cd builtins
static int	cmd_cd(t_cmd *cmd, t_data **prompt)
{
	
	if (chdir(cmd->option[1]))
		return (-2);
	if (update_old_pwd(prompt))
		return (1);
	if (update_pwd(prompt))
		return (1);
	return (0);
}

//execute pwd builtins 
//check how getpwd works if juste retrieve env variable
static int	cmd_pwd(int output)
{
	char	buf[150];

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		write(output, buf, ft_strlen(buf));
		return (0);
	}
	else
	{
		perror("Error with pwd cmd");
		return (1);
	}
}

//check if cmd is builtins, apply the desired cmd

int	check_builtins(int output, t_cmd *cmd, t_data **prompt)
{
	if (!ft_strncmp(cmd->name, "cd", 2))
		return (cmd_cd(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "pwd", 3))
		return (cmd_pwd(output));
	else if (!ft_strncmp(cmd->name, "echo", 4))
		return (cmd_echo(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "export", 6))
		return (cmd_export(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "unset", 5))
		return (cmd_unset(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "env", 3))
		return (cmd_env(output, *prompt));
	else
		return (-2);
}