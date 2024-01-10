/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 05:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/10 08:11:32 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*     todo          */

//protect the write() calls
//between calls to write() open file in append to append the next write

#include "mini_shell.h"

//execute cd builtins
int	cmd_cd(t_cmd *cmd, t_data **prompt)
{
	return (chdir(cmd->option[0]));
}

//execute pwd builtins 
int	cmd_pwd(int output, t_cmd *cmd, t_data **prompt)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		write(output, &buf, ft_strlen(&buf));
		return (0);
	}
	else
	{
		perror("Error with pwd cmd");
		return (-1);
	}
}

//execute echo builtins
int	cmd_echo(int output, t_cmd *cmd, t_data **prompt)
{
	int	i;

	i = 1;
	if (cmd->option[i] == 'n')
		i++;
	while (option[i])
	{
		if (option[i] == '$')
		{
			if (option[i + 1] == '?')
				write(output, ft_itoa((*prompt)->last_status), ft_strlen(ft_itoa((*prompt)->last_status));
			else if (option[i + 1] == ' ')
				write(output,cmd->option[i],ft_strlen(cmd->option[i]);
			else
				write(output, getenv(cmd->option[i] + 1), ft_strlen(getenv(cmd->option[i] + 1)));
			i++;
		}
		write(output, cmd->option[i], ft_strlen(cmd->option[i++]));
	}
	if (cmd->option[1] == 'n')
		write(output, "\n", 1);
	return (0);
}

//execute export builtins
int	cmd_exp_p(int output, char **prompt, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (prompt->env_var[i])
	{
		write(output, "export ", 7);
		write(output, prompt->env_var[i], ft_strlen(prompt->env_var[i]));
		write(output, "\n", 1);
		i++;
	}
	return (0);
}

//execute export builtins
int	cmd_export(t_cmd *cmd, t_data **prompt)
{
	int	i;

	i = 0;
	if (!cmd->option[1])
		return (cmd_exp_p(prompt));
	while (cmd->option[i])
	{
		if (!check_env_var(cmd->option[i]))
		{
			if (!add_env_tab(prompt, cmd->option[i]))
			{
				return (0);
			}
			//nrlmt degage ft_malloc s'en occupe
			else
			{
				perror("Error updating env_tab");
				return (-1);
			}
		}
		else
		{
			perror("Not a valid identifier");
			return (-1);
		}
		i++;
	}
}

//execute unset builtins
int	cmd_unset(t_cmd *cmd, t_data **prompt)
{
	int	i;

	i = 0;
	while (cmd->option[i])
	{
	if (valid_var(cmd->option[i]))
		{
			if (!del_env_tab(prompt, cmd->option[i]))
			{
				return (0);
			}
			else
			{
				perror("Error unset cmd");
				return (-1);
			}
		}
		else
		{
			perror("Not a valid identifier");
			return (-1);
		}
		i++;
	}
}

//execute env builtins & update $?
int	cmd_env(int output, t_cmd *cmd, t_data **prompt)
{
	int	i;

	while (prompt->env[i])
	{
		write(output, prompt->env[i], ft_strlen(prompt->env[i]));
		write(output, "\n", 1);
		i++;
	}
	return (0);
}

//check if cmd is builtins, apply the desired cmd

int	check_builtins(int output, t_cmd *cmd, t_data **prompt)
{
	if (!ft_strncmp(cmd->name, "cd", ft_strlen(cmd->name)))
		return (cmd_cd(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "pwd", ft_strlen(cmd->name)))
		return (cmd_pwd(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "echo", ft_strlen(cmd->name)))
		return (cmd_echo(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "export", ft_strlen(cmd->name)))
		return (cmd_export(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "unset", ft_strlen(cmd->name)))
		return (cmd_unset(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name)))
		return (cmd_exit(cmd, prompt));
	else if (!ft_strncmp(cmd->name, "env", ft_strlen(cmd->name)))
		return (cmd_env(output, cmd, prompt));
	else
		return (-2);
}