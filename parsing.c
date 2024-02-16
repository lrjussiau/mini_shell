/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:52:50 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/16 10:35:26 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_pipe(char *str, t_cmd *cmd, t_data *data)
{
	char	**strs;
	int		i;

	strs = ft_smart_split(str, ' ');
	i = 0;
	while (strs[i] != NULL)
	{
		if (ft_strnstr(strs[i], ">>", ft_strlen(">>")) != 0)
			i += get_fd_append(strs, i, cmd);
		else if (ft_strnstr(strs[i], ">", ft_strlen(">")) != 0)
			i += get_fd_output(strs, i, cmd);
		if (ft_strnstr(strs[i], "<<", ft_strlen("<<")) != 0)
			i += get_fd_limiter(strs, i, cmd);
		else if (ft_strnstr(strs[i], "<", ft_strlen("<")) != 0)
			i += get_fd_input(strs, i, cmd);
		if (!is_inout(strs[i]) && strs[i][0] != '\0')
			i += get_cmd(strs, i, cmd, data);
		i++;
	}
	ft_free_tab(strs);
}

void	parse_input(char *str, t_data *data, t_cmd *current)
{
	char	**strs;
	int		i;

	strs = ft_smart_split(str, '|');
	i = 0;
	while (strs[i] != NULL && *strs[i] != 0)
	{
		process_pipe(strs[i], current, data);
		i++;
		if (strs[i] != NULL && *strs[i] != 0)
			current->is_pipe = true;
		append_cmd(data);
		current = current->next;
	}
	ft_free_tab(strs);
	data->nb_pipe = (i - 1);
	if (data->cmd->name != NULL)
		apply_cmds(data);
	ft_free_input(data);
}

int	init_parsing(char	*str, t_data *data)
{
	t_cmd	*current;

	if (*str == 0)
		return (0);
	data->cmd = init_cmd();
	current = data->cmd;
	if (checker(data) != 0)
	{
		ft_free_input(data);
		return (1);
	}
	parse_input(str, data, current);
	return (0);
}

void	get_input(t_data *data)
{
	char	*input;
	int		n;

	n = 0;
	while (n != 1)
	{
		run_signals(1);
		input = readline("Mini Shell > ");
		if (input == NULL)
			exit(0);
		if (*input)
			add_history(input);
		data->str = ft_strdup(input);
		init_parsing(input, data);
		free(input);
		free(data->str);
	}
}
