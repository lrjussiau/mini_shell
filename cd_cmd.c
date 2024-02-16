/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:58:27 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/16 09:47:54 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	len_dollar(char *str)
{
	int		i;
	int		j;
	int		lent;

	i = 0;
	j = 0;
	lent = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			j = i;
			while (str[j] != ' ' && str[j])
				j++;
			lent = j - i;
			break ;
		}
		i++;
	}
	return (ft_strlen(getenv(ft_substr(str, i, lent))) + len(str) - (j - i));
}

char	*dollar_str(char *str)
{
	char	*ret_str;
	int		i;
	int		j;
	int		len;

	len = len_dollar(str);
	ret_str = malloc((len + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			j = i;
			while (str[j] != ' ' && str[j])
				j++;
			len = j - i;
			break ;
		}
		ret_str[j++] = str[i++];
	}
	ret_str = ft_strcat(ret_str, getenv(ft_substr(str, i, len)));
	return (ret_str);
}

static int	handle_case_cd(t_cmd *cmd, t_data **prompt)
{
	char	*str;

	if (!ft_strncmp(cmd->option[1], "-", len(cmd->option[1])))
	{
		if (env_var_exist((*prompt)->env, "OLDPWD"))
			printf("%s\n", find_old((*prompt)->env));
		else
			printf("minishell: cd: OLDPWD not set\n");
	}
	else if (!ft_strncmp(cmd->option[1], "~", len(cmd->option[1])))
		chdir(getenv("HOME"));
	else if (ft_strchr(cmd->option[1], '$'))
	{
		str = dollar_str(cmd->option[1]);
		if (chdir(str))
		{
			printf("Minishell: cd: %s:no such file or directory\n", str);
			free(str);
			return (-3);
		}
		free(str);
	}
	if (update_old_pwd(prompt) && update_pwd(prompt))
		return (1);
	return (0);
}

//execute cd builtins
int	cmd_cd(t_cmd *cmd, t_data **prompt)
{
	if (!cmd->option[1])
		return (0);
	if (!ft_strncmp(cmd->option[1], "-", len(cmd->option[1]))
		|| ft_strchr(cmd->option[1], '$')
		|| !ft_strncmp(cmd->option[1], "~", len(cmd->option[1])))
	{
		return (handle_case_cd(cmd, prompt));
	}
	if (chdir(cmd->option[1]))
	{
		printf("Minishell: cd: %s:no such file or directory\n", cmd->option[1]);
		return (-3);
	}
	if (update_old_pwd(prompt))
		return (1);
	if (update_pwd(prompt))
		return (1);
	return (0);
}
