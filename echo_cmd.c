/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:16:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/19 11:40:00 by ljussiau         ###   ########.fr       */
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

int	write_dollar(int output, char *str, t_data *da)
{
	int		i;
	int		n;
	char	*ls;

	i = 0;
	n = 0;
	ls = ft_itoa(da->last_status);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			write(output, ls, ft_strlen(ls));
		else if (str[i] == '$' && str[i + 1] != ' ')
		{
			while (str[i++] != ' ' && str[i] && str[i] != '"')
				n++;
			i -= n;
			free(ls);
			ls = ft_substr(str, i, n);
			if (env_var_exist(da->env, ls))
				write(output, getenv(ls), ft_strlen(getenv(ls)));
		}
		i++;
	}
	free(ls);
	return (n);
}

void	process_dollar(int output, char *str, t_data *prompt)
{
	int		i;
	int		is_dquote;
	int		is_quote;

	i = 0;
	is_dquote = 0;
	is_quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			is_dquote++;
		else if (str[i] == '\'')
			is_quote++;
		else if (str[i] == '$' && is_quote % 2 == 0 && str[i + 1])
		{
			i++;
			if (str[i] == ' ')
				write(output, "$ ", 2);
			if (str[i] == '$')
				write(output, "$$", 2);
			else
				i += write_dollar(output, str, prompt);
		}
		else
			write(output, &str[i], 1);
		i++;
	}
}

void	process_quote(int output, char *str)
{
	int		i;
	int		is_dquote;
	int		is_quote;

	i = 0;
	is_dquote = 0;
	is_quote = 0;
	while (str[i])
	{
		if (str[i] == '"' && is_quote % 2 == 0)
			is_dquote++;
		else if (str[i] == '\'' && is_dquote % 2 == 0)
			is_quote++;
		else
			write(output, &str[i], 1);
		i++;
	}
}

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

int	cmd_echo(int output, t_cmd *cmd, t_data **prompt)
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
		if (ft_strnstr(cmd->option[i], "$", ft_strlen(cmd->option[i])) != 0)
			process_dollar(output, cmd->option[i], *prompt);
		else if (ft_strnstr(cmd->option[i], "'", len(cmd->option[i])) != 0)
			process_quote(output, cmd->option[i]);
		else if (ft_strnstr(cmd->option[i], "\"", len(cmd->option[i])) != 0)
			process_quote(output, cmd->option[i]);
		else
			process_classic(output, cmd->option[i]);
		write (output, " ", 1);
		i++;
	}
	if (!is_echo_n(cmd->option[1]))
		write(output, "\n", 1);
	return (0);
}