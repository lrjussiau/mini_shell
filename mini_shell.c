/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 07:26:44 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/16 07:37:58 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int argc, char **argv, char **envp)
{
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
	data = init_data(1);
	data->env = envp;
	get_input(data);
	free(data);
	clear_history();
}