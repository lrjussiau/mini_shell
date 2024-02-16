/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:53:18 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/16 10:29:17 by ljussiau         ###   ########.fr       */
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
// # include <readline/readline.h>
// # include <readline/history.h>

# if defined (__APPLE__)
#  include <readline/history.h>
#  include <readline/readline.h>
# else
#  include <sys/wait.h>
#  include </home/linuxbrew/.linuxbrew/opt/readline/include/readline/history.h>
#  include </home/linuxbrew/.linuxbrew/opt/readline/include/readline/readline.h>
# endif

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
char	*ft_append_str(char *str, char *input);
void	parse_input(char *str, t_data *data, t_cmd *current);
void	process_pipe(char *str, t_cmd *cmd, t_data *data);
int		get_cmd(char **strs, int i, t_cmd *cmd, t_data *data);

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
void	append_cmd(t_data *data);
void	append_input(t_cmd *cmd);
void	append_output(t_cmd *cmd);

//handle error
void	free_array(int i, char **array);
void	ft_free_input(t_data *data);
void	error_handle(t_data *data, char *error);

//checker
int		checker(t_data *data);
void	check_limiter(t_data *data);
void	check_quote(t_data *data);
char	*get_limiter(char *str);

//smart split
char	**ft_smart_split(char *s, char c);

//signal
void	signal_handler(int signal_num);

//other
void	print_data(t_data *data);

//execute
int		apply_cmds(t_data *prompt);
void	free_fdtab(int **tab);

//builtins
int		check_builtins(int output, t_cmd *cmd, t_data **prompt);

//builtins_utils
int		add_env_tab(t_data **prompt, char *env_var, int n);
int		del_env_tab(t_data **prompt, char *env_var, int n);
char	**ft_copy_or(char	**strs);

//exec_utils
int		fd_error(int input);
char	*ft_conc(char *str, char *input);
char	*cmd_path(char *cmd, char **envp);
char	*find_old(char **envp);
int		is_echo_n(char *cmd_option);

//bin_exec
char	*find_path(char *cmd, char *paths);
char	*find_exec_path(char *cmd, char **envp, char *paths);

//input_output
int		find_input(t_cmd *cmd, int **fd_tab, int *k, char *str);
int		find_output(t_cmd *cmd, int **fd_tab, int *k);

//fd_tab
void	ft_close(int **fd_tab);
void	printf_fdtab(int **fd_tab);
int		**create_fd_tab(int pipe_nbr, int **fd_tab);
int		find_pipe_nb(t_data *prompt);

//echo_cmd
int		cmd_echo(int output, t_cmd *cmd);
int		miteux(char *str, int le);

//env_var_check
int		valid_var(char *env_var);
int		check_env_var(char	*var, t_data **prompt);
int		env_var_exist(char **env_var_tab, char *env_var);
char	*ft_getenv(char *str, t_data *data);

//env_var_cmd
int		cmd_unset(t_cmd *cmd, t_data **prompt);
int		cmd_env(int output, t_data *prompt);
int		cmd_export(int output, t_cmd *cmd, t_data **prompt);

//signal
void	run_signals(int sig);
int		update_old_pwd(t_data **prompt);
int		update_pwd(t_data **prompt);
int		cmd_cd(t_cmd *cmd, t_data **prompt);

//dolar
char	*ft_process_dolar(char *str, t_data *data);
char	*replace_dollar(char *str, t_data *data);
char	*get_dollar(char *str, char *ret_str, char *env, char *env_name);
char	*process_status(char *str, t_data *data);
char	*get_env_name(char *str);
int		len_str(char *str, char *lst_st);
int		len_str_env(char *str, char *env, char *env_name);

//origin_handler
char	**ft_copy_or(char	**strs);
char	*add_quote(char *str);
int		update_pwd_or(t_data **prompt);
int		update_old_pwd_or(t_data **prompt);
#endif