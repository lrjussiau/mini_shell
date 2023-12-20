/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:53:18 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/19 11:26:53 by ljussiau         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	*cmd;
	char	*option;
	bool	is_output_fd;
	bool	is_output_append;
	char	**output_fd;
	bool	is_input_fd;
	bool	is_input_limiter;
	char	**input_fd;
	char	**input_limiter;
	void	*next;
}		t_cmd;

typedef struct s_env
{
	char	*NAME;
	char	*value;
	void	*next;
}		t_env;

typedef struct s_data
{
	char	*str;
	t_cmd	cmd;
	int		nb_pipe;
	bool	is_env;
	t_env	env_var;
	int		var;
}		t_data;

int	check_output(char **strs, int i, t_data *data);
int	get_fd_output(char **strs, int i, t_data *data);
int	get_fd_append(char **strs, int i, t_data *data);

#endif