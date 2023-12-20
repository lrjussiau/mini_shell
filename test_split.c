/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:52:50 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/20 08:49:04 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_pipe(char *str, t_data *data)
{
	char	**strs;
	int		i;

	strs = ft_split(str, ' ');
	i = 0;
	while (strs[i] != NULL)
	{
		i += check_output(strs, i, data);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**strs;
	int		i;
	t_data	*data;

	argc = 0;
	strs = ft_split(argv[1], '|');
	i = 0;
	data = init_data(data);
	while (strs[i] != NULL)
	{
		//create node
		process_pipe(strs[i], data);
		printf("Next pipe\n");
		i++;
	}
	if (data -> cmd -> is_output_append == true)
	{
		printf("test\n");
	}
}
