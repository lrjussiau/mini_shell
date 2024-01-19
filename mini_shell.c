/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 07:26:44 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/19 11:00:44 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		return (0);
	argv = NULL;
	data = init_data(1);
	data->env = ft_copy_tab(envp);
	get_input(data);
	ft_free_tab(data->env);
	free(data);
	clear_history();
}
