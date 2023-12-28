/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 05:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2023/12/28 12:01:34 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*what i need*/


/*In t_data struct change:t_env *env_var (linked list) 
to: char **env_var_tab ->(execve, simplicity to add/rm element)*/

/*add field in t_data -> char *original_PATH
pour cmd: env -l "cmd" = execute command with clean $PATH
->keep a copy of the clean $PATH at initialisation of the programm*/

/*------------------------------------------------------------------------------*/

/*to discuss*/


/*when do we clean/shut-down the programm -> only when supposed to "crash" like a real shell?->every maloc?*/

/*clean_all function ->clean the t_data structure with underlying structures->own malloc function with exit if bad alloc?*/

/*cmd->option =  cmd, flags type: '-' (flags), other args*/

#include "mini_shell.h"

//execute cd builtins & update $?

int	cmd_cd(t_cmd *cmd, t_data **prompt)
{
	(*prompt)->last_status = chdir(cmd->option[0]);
	return (0);
}

//execute pwd builtins & update $?

int	cmd_pwd(t_cmd *cmd, t_data **prompt)
{
	char	buf[PATH_MAX]

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		fd_printf(last_output(cmd), "%s", buf);
		(*prompt)->last_status = 0;
		return (0);
	}
	else
	{
		perror("Error with pwd cmd");
		(*prompt)->last_status = -1;
		return (0);
	}
}

//execute echo builtins & update $?

int	cmd_echo(t_cmd *cmd, t_data **prompt)
{
	if (cmd->option[0] == 'n')
	{
		fd_printf(last_output(cmd), "%s\n", cmd->option[1]);
		(*prompt)->last_status = 0;
		return (0);
	}
	else
	{
		fd_printf(last_output(cmd), "%s", cmd->option[1]);
		(*prompt)->last_status = 0;
		return (0);
	}
}

//execute export -p builtins & update $?

int	cmd_exp_p(char **prompt, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (prompt->env_var[i])
	{
		fd_printf(last_output(cmd), "export %s\n", prompt->env_var[i]);
		i++;
	}
	(*prompt)->last_status = 0;
	return (0);
}

//to do? if environement with same name replace value with new one?(yes)

//execute export builtins & update $?

int	cmd_export(t_cmd *cmd, t_data **prompt)
{
	int	i;

	i = 0;
	if (cmd->option[0] == 'p')
		return (cmd_exp_p(prompt));
	while (cmd->option[i])
	{
		if (!check_env_var(cmd->option[i]))
		{
			if (!add_env_tab(prompt, cmd->option[i]))
			{
				(*prompt)->last_status = 0;
				return (0);
			}
			else
			{
				perror("Error updating env_tab");
				(*prompt)->last_status = -1;
				return (-1);
			}
		}
		else
		{
			perror("Invalid environment variable provided");
			(*prompt)->last_status = -1;
			return (0);
		}
		i++;
	}
}

//execute unset builtins & update $?

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
				prompt->last_status = 0;
				return (0);
			}
			else
			{
				perror("Error unset cmd");
				prompt->last_status = -1;
				return (-1);
			}
		}
		else
		{
			perror("Invalid identifier");
			prompt->last_status = -1;
			return (-1);
		}
		i++;
	}
}

//execute env builtins & update $?

int	cmd_env(t_cmd *cmd, t_data **prompt)
{
	int	i;

	i = 0;
	if (!cmd->option[0])
	{
		if (exec_env_cmd(cmd, prompt))
		{
			prompt->last_status = 0;
			return (0);
		}
		else
		{
			prompt->last_status = -1;
			return (-1);
		}
	}
	else
	{
		while (prompt->env_var[i])
		{
			//fd_printf(last_output(cmd), %s\n, prompt->env_var[i++]);
		}
		prompt->last_status = 0;
		return (0);
	}
}

//check if cmd is builtins, apply the desired cmd

int	check_builtins(t_cmd *cmd, t_data *prompt)
{
	if (cmd->name == "cd")
		return (cmd_cd(cmd, &prompt));
	else if (cmd->name == "pwd")
		return (cmd_pwd(cmd, &prompt));
	else if (cmd->name == "echo")
		return (cmd_echo(cmd, &prompt));
	else if (cmd->name == "export")
		return (cmd_export(cmd, &prompt));
	else if (cmd->name == "unset")
		return (cmd_unset(cmd, &prompt));
	else if (cmd->name == "exit")
		return (cmd_exit(cmd, &prompt));
	else if (cmd->name == "env")
		return (cmd_env(cmd, &prompt));
}