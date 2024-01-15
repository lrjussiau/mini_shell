/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:52:50 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/15 11:36:44 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <unistd.h>

void	signal_handler(int signal_num)
{
	if (signal_num == 2)
	{
		printf("You Print Ctrl + C\n");
	}
}

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

void	parse_input(char *str, t_data *data)
{
	char	**strs;
	int		i;
	t_cmd	*current;

	if (*str == 0)
		return ;
	data->cmd = init_cmd();
	current = data->cmd;
	data->str = ft_strdup(str);
	check_limiter(data);
	check_quote(data);
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
	// print_data(data); 
	printf("last status: %d\n", apply_cmds(data));//ici sera l'execute
	ft_free_input(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		n;
	t_data	*data;

	if (argc != 1)
		return (0);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		printf("Error setting up signal handler.\n");
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	argv = NULL;
	n = 0;
	data = init_data(1);
	data->env = envp;
	while (n != 1)
	{
		input = readline("Mini Shell > ");
		if (input == NULL)
		{
			printf("\nThank you !\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (ft_strnstr(input, "exit", ft_strlen(input)) != 0)
		{
			n = 1;
			free(input);
			break ;
		}
		parse_input(input, data);
		free(input);
		free(data->str);
	}
	free(data);
	clear_history();
}
