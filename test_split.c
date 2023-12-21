/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:52:50 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/21 09:47:47 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_pipe(char *str, t_cmd *cmd)
{
	char	**strs;
	int		i;

	strs = ft_split(str, ' ');
	i = 0;
	while (strs[i] != NULL)
	{
		if (ft_strnstr(strs[i], ">>", ft_strlen(strs[i])) != 0)
			i += get_fd_append(strs, i, cmd);
		else if (ft_strnstr(strs[i], ">", ft_strlen(strs[i])) != 0)
			i += get_fd_output(strs, i, cmd);
		if (ft_strnstr(strs[i], "<", ft_strlen(strs[i])) != 0)
			printf("input\n");
		else if (ft_strnstr(strs[i], "<<", ft_strlen(strs[i])) != 0)
			printf("input limiter\n");
		//process_cmd
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**strs;
	int		i;
	t_data	*data;
	t_cmd	*current;

	data = init_data();
	current = data->cmd;
	strs = ft_split(argv[1], '|');
	i = 0;
	while (strs[i] != NULL)
	{
		printf("'%d'\n", i);
		process_pipe(strs[i], current);
		i++;
		if (strs[i] != NULL)
			current->is_pipe = true;
		append_cmd(data);
		current = current->next;
	}
	print_data(data);
}
