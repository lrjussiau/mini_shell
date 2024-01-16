/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:53:18 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/16 07:49:55 by ljussiau         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_inout
{
	bool			is_fd;
	bool			is_append;
	bool			is_limiter;
	char			*name;
	struct s_inout	*next;
}		t_inout;

typedef struct s_cmd
{
	char			*name;
	char			**option;
	t_inout			*output;
	t_inout			*input;
	bool			is_pipe;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_data
{
	char	*str;
	t_cmd	*cmd;
	int		nb_pipe;
	bool	is_env;
	char	**env;
	char	**origin;
	int		last_status;
}		t_data;

//parsing inout
int		get_fd_output(char **strs, int i, t_cmd *cmd);
int		get_fd_append(char **strs, int i, t_cmd *cmd);
int		get_fd_input(char **strs, int i, t_cmd *cmd);
int		get_fd_limiter(char **strs, int i, t_cmd *cmd);

//parsing cmd
void	get_input(t_data *data);
void	parse_input(char *str, t_data *data, t_cmd *current);
void	process_pipe(char *str, t_cmd *cmd);
int		get_cmd(char **strs, int i, t_cmd *cmd);

//parsing tool
bool	is_inout(char *str);
int		len(const char *str);
char	*ft_strcat(char *s1, char *s2);
char	**ft_copy_tab(char	**strs);

//struct init
t_data	*init_data(int n);
t_cmd	*init_cmd(void);
t_inout	*init_inout(void);

//tool struct
void	print_data(t_data *data);
void	append_cmd(t_data *data);
void	append_input(t_cmd *cmd);
void	append_output(t_cmd *cmd);
//handle error
void	ft_free_input(t_data *data);
void	ft_free_env(t_data *data);
void	error_handle(t_data *data, char *error);

//checker
char	*ft_append_str(char *str, char *input);
void	check_limiter(t_data *data);
void	check_quote(t_data *data);

//val exec
int		apply_cmds(t_data *prompt);
int		check_builtins(int output, t_cmd *cmd, t_data **prompt);

//val builtins utils
int		add_env_tab(t_data **prompt, char *env_var);
int		del_env_tab(t_data **prompt, char *env_var);
int		valid_var(char *env_var);
int		check_env_var(char	*var);

//smart split
char	**ft_smart_split(char *s, char c);

//Signal
void	signal_handler(int signal_num);

#endif