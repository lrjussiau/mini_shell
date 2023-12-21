/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:53:18 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/21 09:42:35 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdbool.h>

typedef struct s_env
{
	char	*name;
	char	*value;
	void	*next;
}		t_env;

typedef struct s_inout
{
	bool	is_fd;
	bool	is_append;
	bool	is_limiter;
	char	*name;
	void	*next;
}		t_inout;

typedef struct s_cmd
{
	char		*cmd;
	char		*option;
	t_inout		*output;
	t_inout		*input;
	bool		is_pipe;
	void		*next;
}		t_cmd;

typedef struct s_data
{
	char	*str;
	t_cmd	*cmd;
	int		nb_pipe;
	bool	is_env;
	t_env	env_var;
	int		last_status;
}		t_data;

int		get_fd_output(char **strs, int i, t_cmd *cmd);
int		get_fd_append(char **strs, int i, t_cmd *cmd);
t_data	*init_data(void);
t_cmd	*init_cmd(void);
t_inout	*init_inout(void);
void	print_data(t_data *data);
void	append_cmd(t_data *data);
void	append_input(t_cmd *cmd);
void	append_output(t_cmd *cmd);

#endif