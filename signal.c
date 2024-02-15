/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:56:42 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/15 10:13:30 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

void	restore_prompt(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}

void	heredoc(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	// printf("pid inside signal: %d\n", getpid());
}

void	run_signals(int sig)
{
	// printf("sig : %d\n", sig);
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
	if (sig == 4)
	{
		signal(SIGINT, heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
