/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:23:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/29 14:56:16 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_close(int **fd_tab)
{
	int	i;

	i = 1;
	while (fd_tab[i])
	{
		close(fd_tab[i][0]);
		close(fd_tab[i][1]);
		i++;
	}
}

void	printf_fdtab(int **fd_tab)
{
	int	i;

	i = 0;
	while (fd_tab[i])
	{
		printf("in : %d\n", fd_tab[i][0]);
		printf("out : %d\n\n", fd_tab[i][1]);
		i++;
	}
}

int	**create_fd_tab(int pipe_nbr, int **fd_tab)
{
	int	i;

	i = 0;
	fd_tab = malloc(sizeof (int *) * (pipe_nbr) + 2);
	if (!fd_tab)
		return (0);
	while (pipe_nbr)
	{
		fd_tab[i] = malloc(sizeof(int) * 2);
		if (!fd_tab[i])
		{
			free_fdtab(fd_tab);
			printf("error\n");
			return (0);
		}
		if (pipe(fd_tab[i++]) == -1)
		{
			free_fdtab(fd_tab);
			return (0);
		}
		pipe_nbr--;
	}
	fd_tab[i] = 0;
	return (fd_tab);
}

int	find_pipe_nb(t_data *prompt)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;

	cmd = prompt->cmd;
	i = 0;
	while (cmd->next->next)
	{
		if (!(cmd->output->next) && !(cmd->output->name))
		{	
			tmp = cmd->next;
			if (!(tmp->input->next) && !(tmp->input->name))
				i++;
		}
		cmd = cmd->next;
	}
	return (i);
}
