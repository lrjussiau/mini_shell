/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:58:02 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/16 10:27:50 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*replace_dollar(char *str, t_data *data)
{
	char	*ret_str;
	char	*env;
	char	*env_name;

	env_name = get_env_name(str);
	if (!env_var_exist(data->env, env_name))
	{
		free(env_name);
		return (ft_strdup(str));
	}
	env = ft_getenv(env_name, data);
	ret_str = malloc(sizeof(char) * (len_str_env(str, env, env_name) + 1));
	ret_str = get_dollar(str, ret_str, env, env_name);
	free(env_name);
	return (ret_str);
}

char	*ft_process_dolar(char *str, t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
				str = process_status(str, data);
			else
				str = replace_dollar(str, data);
			n += 1;
		}
		i++;
	}
	if (n == 0)
		return (ft_strdup(str));
	else
		return (str);
}

char	*cleaner_option(char *str, t_data *data)
{
	int		i;
	char	*ret_str;

	i = 0;
	if (str[i] == '\'')
	{
		str = ft_strtrim(str, "'");
	}
	else if (str[i] == '"')
	{
		ret_str = ft_strtrim(str, "\"");
		str = ft_process_dolar(ret_str, data);
		free(ret_str);
	}
	else
	{
		str = ft_process_dolar(str, data);
	}
	return (str);
}

char	*ft_append_str(char *str, char *input)
{
	char	*ret_str;
	int		i;
	int		j;

	ret_str = malloc((ft_strlen(str) + ft_strlen(input) + 2) * sizeof(char));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret_str[i] = str[i];
		i++;
	}
	ret_str[i++] = '\n';
	j = 0;
	while (input[j])
	{
		ret_str[i + j] = input[j];
		j++;
	}
	ret_str[i + j] = '\0';
	return (ret_str);
}

int	get_cmd(char **strs, int i, t_cmd *cmd, t_data *data)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	cmd->name = cleaner_option(strs[i], data);
	i++;
	while (strs[i] != NULL)
	{
		if (is_inout(strs[i]))
			break ;
		i++;
		j++;
	}
	i -= j + 1;
	cmd->option = (char **)malloc(sizeof(char *) * (j + 2));
	while (k <= j)
	{
		cmd->option[k] = cleaner_option(strs[i], data);
		i++;
		k++;
	}
	cmd->option[k] = NULL;
	return (j);
}
