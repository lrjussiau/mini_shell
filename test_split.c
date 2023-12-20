/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:52:50 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/20 11:31:33 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_pipe(char *str, t_data *data)
{
	char	**strs;
	int		i;

	strs = ft_split(str, ' ');
	i = 0;
	data->cmd->nb_output = get_nb_output(strs);
	while (strs[i] != NULL)
	{
		printf("%s\n", strs[i]);
		i += check_output(strs, i, data);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**strs;
	int		i;
	t_data	*data;
	t_cmd	*current;

	argc = 0;
	strs = ft_split(argv[1], '|');
	i = 0;
	data = init_data();
	while (strs[i] != NULL)
	{
		current = init_cmd();
		append_cmd(data, current);
		process_pipe(strs[i], data);
		i++;
	}
	print_data(data);
}
