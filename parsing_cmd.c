/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:58:02 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/16 08:25:41 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*cleaner_option(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (ft_strnstr(cmd->name, "echo", ft_strlen("echo")) != 0)
		return (ft_strdup(str));
	else
	{
		if (str[i] == '\'')
		{
			str = ft_strtrim(str, "'");
			return (str);
		}
		else if (str[i] == '"')
		{
			str = ft_strtrim(str, "\"");
			return (str);
		}
		else
			return (ft_strdup(str));
	}
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

int	get_cmd(char **strs, int i, t_cmd *cmd)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	cmd->name = ft_strdup(strs[i]);
	while (strs[i] != NULL)
	{
		i++;
		if (is_inout(strs[i]))
			break ;
		j++;
	}
	i -= j + 1;
	cmd->option = (char **)malloc(sizeof(char *) * (j + 2));
	while (k <= j)
	{
		cmd->option[k] = cleaner_option(strs[i], cmd);
		i++;
		k++;
	}
	cmd->option[k] = NULL;
	return (j);
}
