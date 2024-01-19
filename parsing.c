/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:52:50 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/19 15:07:41 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_pipe(char *str, t_cmd *cmd)
{
	char	**strs;
	int		i;

	strs = ft_smart_split(str, ' ');
	i = 0;
	while (strs[i] != NULL)
	{
		if ((ft_strnstr(strs[i], ">>", ft_strlen(strs[i])) != 0))
			i += get_fd_append(strs, i, cmd);
		else if (ft_strnstr(strs[i], ">", ft_strlen(strs[i])) != 0)
			i += get_fd_output(strs, i, cmd);
		if (ft_strnstr(strs[i], "<<", ft_strlen(strs[i])) != 0)
			i += get_fd_limiter(strs, i, cmd);
		else if (ft_strnstr(strs[i], "<", ft_strlen(strs[i])) != 0)
			i += get_fd_input(strs, i, cmd);
		if (!is_inout(strs[i]) && strs[i][0] != '\0')
			i += get_cmd(strs, i, cmd);
		i++;
	}
	ft_free_tab(strs);
}

void	parse_input(char *str, t_data *data, t_cmd *current)
{
	char	**strs;
	int		i;

	strs = ft_split(str, '|');
	i = 0;
	while (strs[i] != NULL)
	{
		process_pipe(strs[i], current);
		i++;
		if (strs[i] != NULL)
			current->is_pipe = true;
		append_cmd(data);
		current = current->next;
	}
	ft_free_tab(strs);
	data->nb_pipe = (i - 1);
	print_data(data);
	if (data->cmd->name != NULL)
		apply_cmds(data);
	ft_free_input(data);
}

void	init_parsing(char	*str, t_data *data)
{
	t_cmd	*current;

	if (*str == 0)
		return ;
	data->cmd = init_cmd();
	current = data->cmd;
	if (checker(data) != 0)
		return ;
	parse_input(str, data, current);
}

void	get_input(t_data *data)
{
	char	*input;
	int		n;

	n = 0;
	run_signals(1);
	while (n != 1)
	{
		input = readline("Mini Shell > ");
		if (input == NULL)
			exit(0);
		if (*input)
			add_history(input);
		if (ft_strnstr(input, "exit", ft_strlen(input)) != 0)
		{
			n = 1;
			free(input);
			break ;
		}
		data->str = ft_strdup(input);
		init_parsing(input, data);
		free(input);
		free(data->str);
	}
}
