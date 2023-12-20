typedef struct s_cmd
{
	char		*cmd;
	char		*option;
	t_inout		*output;
	t_inout		*input;
	void		*next;
	bool		is_pipe;
}		t_cmd;

typedef	struct s_inout
{
	bool	is_fd;
	bool	is_append;
	bool	is_limiter;
	char	*name;
	void	*next;
}		t_inout;

typedef struct s_env
{
	char	*name;
	char	*value;
	void	*next;
}		t_env;

typedef struct s_data
{
	char	*str;
	t_cmd	*cmd;
	int		nb_pipe;
	bool	is_env;
	t_env	env_var;
	int		last_status;
}		t_data;

int		check_output(char **strs, int i, t_data *data);
int		get_fd_output(char **strs, int i, t_data *data);
int		get_fd_append(char **strs, int i, t_data *data);
t_data	*init_data(void);
t_cmd	*init_cmd(void);
void	print_data(t_data *data);
void	append_cmd(t_data *data, t_cmd *new_cmd);
int		get_nb_output(char **strs);
char	**add_strs(char **strs, char *str, int nb);

#endif