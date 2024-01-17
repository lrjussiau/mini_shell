/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:16:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/17 06:54:57 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	is_echo_n(char *cmd_option)
{
	if (ft_strlen(cmd_option) == 2 && cmd_option[0] == '-'
		&& cmd_option[1] == 'n')
		return (1);
	return (0);
}

static void	clean_quote(char **option, char **is_dollar)
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
	char	*dollar_str;
	char	*opt;

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
		dollar_str = ft_strchr(cmd->option[i], '$');
		clean_quote(&cmd->option[i], &dollar_str);
		opt = cmd->option[i];
		str = ft_strchr(opt, '$');
		if (dollar_str)
		{
			write(output, opt, ft_strlen(opt) - ft_strlen(str));
			if (str[1] == '?')
				write(output, ft_itoa((*prompt)->last_status), ft_strlen(ft_itoa((*prompt)->last_status)));
			else if (!str[1])
				write(output, "$", 1);
			else if (env_var_exist((*prompt)->env, str + 1))
				write(output, getenv(str + 1), ft_strlen(getenv(str + 1)));
			else
			{
				write(output, opt, ft_strlen(opt));
				if (cmd->option[i + 1])
					write(output, " ", 1);
			}
		}
		else
		{
			write(output, opt, ft_strlen(opt));
			if (cmd->option[i + 1])
				write(output, " ", 1);
		}
		i++;
	}
	if (is_echo_n(cmd->option[1]))
		write(output, "\n", 1);
	return (0);
}