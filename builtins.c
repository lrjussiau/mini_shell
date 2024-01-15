/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 05:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/15 11:57:02 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*     todo          */

//protect the write() calls
//between calls to write() open file in append to append the next write
//limiter
//trim single quotes/double quotes echo


#include <stdio.h>
#include "mini_shell.h"

//execute cd builtins
int	cmd_cd(t_cmd *cmd)
{
	return (chdir(cmd->option[1]));
}

//execute pwd builtins 
//check how getpwd works if juste retrieve env variable
int	cmd_pwd(int output)
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
		return (-1);
	}
}

int	is_echo_n(char *cmd_option)
{
	if (ft_strlen(cmd_option) == 2 && cmd_option[0] == '-'
		&& cmd_option[1] == 'n')
		return (1);
	return (0);
}

void	clean_cmd(char **option, char **is_dollar)
{
	char	*new_str;

	if (*is_dollar)
	{
		if ((*option)[0] == '"')
			new_str = ft_strtrim(*option, "\"");
		else if ((*option)[0] == '\'' )
		{
			new_str = ft_strtrim(*option, "'");
			*is_dollar = 0;
		}
		else
			return ;
		free(*option);
		(*option) = new_str;
		printf("option: %s\n", (*option));
	}
	else
	{
		if ((*option)[0] == '"')
			new_str = ft_strtrim(*option, "\"");
		else if ((*option)[0] == '\'' )
			new_str = ft_strtrim(*option, "'");
		else
			return ;
		free(*option);
		(*option) = new_str;
	}
	return ;
}
//execute echo builtins
int	cmd_echo(int output, t_cmd *cmd, t_data **prompt)
{
	int		i;
	char	*str;
	char	*str2;
	char	*opt;

	i = 1;
	if (is_echo_n(cmd->option[1]))
		i++;
	while (cmd->option[i])
	{
		str2 = ft_strchr(cmd->option[i], '$');
		clean_cmd(&cmd->option[i], &str2);
		opt = cmd->option[i];
		str = ft_strchr(opt, '$');
		if (str2)
		{
			printf("optio: %c\n", str[1]);
			write(output, opt, ft_strlen(opt) - ft_strlen(str));
			if (str[1] == '?')
				write(output, ft_itoa((*prompt)->last_status), ft_strlen(ft_itoa((*prompt)->last_status)));
			else if (!str[1])
				write(output, "$", 1);
			else
				write(output, getenv(str + 1), ft_strlen(getenv(str + 1)));
		}
		else
		{
			write(output, opt, ft_strlen(opt));
			write(output, " ", 1);
		}
		i++;
	}
	if (is_echo_n(cmd->option[1]))
		write(output, "\n", 1);
	return (0);
}

//execute export builtins
int	cmd_exp_p(int output, t_data *prompt)
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
	//printf("cmd[1]:%s\n", cmd->option[1]);
	//printf("cmd[2]:%s\n", cmd->option[2]);
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

//check if cmd is builtins, apply the desired cmd

int	check_builtins(int output, t_cmd *cmd, t_data **prompt)
{
	if (!ft_strncmp(cmd->name, "cd", 2))
		return (cmd_cd(cmd));
	else if (!ft_strncmp(cmd->name, "pwd", 3))
		return (cmd_pwd(output));
	else if (!ft_strncmp(cmd->name, "echo", 4))
		return (cmd_echo(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "export", 6))
		return (cmd_export(output, cmd, prompt));
	else if (!ft_strncmp(cmd->name, "unset", 5))
		return (cmd_unset(cmd, prompt));
	/*else if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name)))
		return (cmd_exit(cmd, prompt));*/
	else if (!ft_strncmp(cmd->name, "env", 3))
		return (cmd_env(output, *prompt));
	else
		return (-2);
}