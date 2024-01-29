/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:15:06 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/29 13:27:01 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	len_str(char *str, char *lst_st)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			len += ft_strlen(lst_st) - 1;
			i ++;
		}
		i++;
		len++;
	}
	return (len);
}

char	*get_env_name(char *str)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	j = 0;
	while (str[i + j] && str[i + j] != ' ')
		j++;
	word = (char *)malloc(sizeof(char) * (j + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		word[j] = str[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

int	len_str_env(char *str, char *env, char *env_name)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			len += ft_strlen(env) - 1;
			i += ft_strlen(env_name);
		}
		if (str[i] == '\0')
			break ;
		i++;
		len++;
	}
	return (len);
}

char	*process_status(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*ret_str;
	char	*lst_st;

	lst_st = ft_itoa(data->last_status);
	ret_str = malloc(sizeof(char) * (len_str(str, lst_st) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ft_memcpy(&ret_str[j], lst_st, ft_strlen(lst_st));
			j += ft_strlen(ft_itoa(data->last_status));
			i += 2;
		}
		ret_str[j] = str[i];
		i++;
		j++;
	}
	free(lst_st);
	return (ret_str);
}

char	*ft_getenv(char *str, t_data *data)
{
	char	*ret_str;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], str, ft_strlen(str)) != 0)
		{
			ret_str = ft_strchr(data->env[i], '=') + 1;
			return (ret_str);
		}
		i++;
	}
	return (NULL);
}

char	*replace_dollar(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*ret_str;
	char	*env;
	char	*env_name;

	env_name = get_env_name(str);
	if (!env_var_exist(data->env, env_name))
		return (str);
	env = ft_getenv(env_name, data);
	ret_str = malloc(sizeof(char) * (len_str_env(str, env, env_name) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ft_memcpy(&ret_str[j], env, ft_strlen(env)); // ici a voir 
			j += ft_strlen(env);
			i += ft_strlen(env_name) + 1;
		}
		if (str[i] == '\0')
			break ;
		ret_str[j] = str[i];
		i++;
		j++;
	}
	ret_str[j] = '\0';
	free(env_name);
	return (ret_str);
}
