/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:57:23 by vvuadens          #+#    #+#             */
/*   Updated: 2024/01/16 09:00:38 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>


void	fd_error(int input, int output)
{
	if (input == -1 || output == -1)
	{
		printf("Error opening file");
		//ft_clean();
		exit (-1);
	}
}

void	ft_close(int **fd_tab)
{
	int	i;

	i = 0;
	while (fd_tab[i])
	{
		close(fd_tab[i][0]);
		close(fd_tab[i][1]);
		i++;
	}
}

char	*find_path(char *cmd, char *paths)
{
	char	**tab;
	char	*path;
	char	*path2;
	int		i;

	i = 0;
	tab = ft_split(paths, ':');
	if (!tab)
		return (0);
	while (tab[i])
	{
		path = ft_strjoin(tab[i++], "/");
		path2 = ft_strjoin(path, cmd);
		free(path);
		if (access(path2, X_OK) != -1)
		{
			free(cmd);
			//free_tab((void **)tab);
			return (path2);
		}
		free(path2);
	}
	free(cmd);
	//free_tab((void **)tab);
	return (0);
}

char	*find_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", ft_strlen("PWD=")))
			return (ft_strchr(envp[i], '/'));
		i++;
	}
	return (0);
}

char	*ft_conc(char *str, char *input)
{
	char	*ret_str;
	int		i;
	int		j;

	ret_str = malloc((ft_strlen(str) + ft_strlen(input) + 1) * sizeof(char));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret_str[i] = str[i];
		i++;
	}
	j = 0;
	while (input[j])
	{
		ret_str[i + j] = input[j];
		j++;
	}
	ret_str[i + j] = '\0';
	return (ret_str);
}

char	*find_exec_path(char *cmd, char **envp, char *paths)
{
	char	*path;
	
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		if (ft_strchr(cmd + 2, '/'))
		{
			return (cmd);
		}
		else
		{
			path = find_path(cmd, paths);
			if (!path)
				path = find_pwd(envp);
			return(ft_conc(path, cmd + 1));
		}
	}
	else
		return (cmd);
}

char	*cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*paths;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			paths = envp[i] + 5;
		i++;
	}
	if (ft_strchr(cmd, '/'))
		path = find_exec_path(cmd, envp, paths);
	else
		path = find_path(cmd, paths);
	printf("path; %s", path);
	if (!path)
	{
		perror("error to find cmd path");
		exit(1);
	}
	return (path);
}

int execute_cmd( int input, int output, t_cmd *cmd, int **fd_tab, char **envp)
{
	pid_t	child;

	//printf("pat: %s",cmd_path(cmd->name, envp));
	child = fork();
	if (child == 0)
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		ft_close(fd_tab);
		return (execve(cmd_path(cmd->name, envp), cmd->option, envp));
	}
	else if (child > 0)
	{
		wait(&child);
		return 0;
	}
	else
	{
		//free_tab((void **)fd_tab);
		//perror(strerror(errno));
		exit(EXIT_FAILURE);
		return (-1);
	}
}

void	limiter_str(char *limiter, char *prompt, int input_fd)
{
	char	*str;
	char	*after_lim;

	str = ft_strchr(prompt, '\n');
	after_lim = ft_strnstr(str, limiter, ft_strlen(str));
	write(input_fd, str + 1, ((ft_strlen(str + 1) - ft_strlen(after_lim)) - 1));
}

int	find_input_v2(t_cmd *cmd, int **fd_tab, int *k, char *str)
{
	int		input;
	t_inout	*inp;

	inp = cmd->input;
	if (inp->name)
	{
		while (inp->next->next)
			inp = inp->next;
		if (inp->is_fd)
		{
			input = open(inp->name, O_RDONLY);
		}
		else
		{
			input = open("limiter_file", O_WRONLY | O_CREAT |O_TRUNC, 0644);
			fd_error(input, 0);
			limiter_str(inp->name, str, input);
			close(input);
			input = open("limiter_file", O_RDONLY);
		}
	}
	//input given
	else if (*k != 0)
	{
		printf("nmrl\n");
		input = fd_tab[*k][0];
	}
	else
		input = STDIN_FILENO;
	return (input);
}

int	find_output_v2(t_cmd *cmd, int **fd_tab, int *k)
{
	int		output;
	t_inout	*out;

	out = cmd->output;
	if (out->name)
	{
		while (out->next->next)
		{
			open(out->name, O_TRUNC | O_CREAT, 0644);
			out = out->next;
		}
		if (out->is_append || !ft_strncmp(cmd->option[0], "echo", 5))
			output = open(out->name, O_WRONLY | O_APPEND);
		else
			output = open(out->name, O_WRONLY | O_CREAT, 0644);
	}
	else if (cmd->is_pipe)
	{
		cmd = cmd->next;
		if (!(cmd->input->name))
		{
			output = fd_tab[*k + 1][1];
			(*k)++;
		}
		else
			output = STDOUT_FILENO;
	}
	else
		output = STDOUT_FILENO;
	return (output);
}

//check if cmd is builtins, execute the command, update last status
void	execute(int input, int output, t_cmd *cmd, t_data **prompt, int **fd_tab)
{
	int	status;

	//printf("cmd: input = %d, output = %d, cmd= %s", input, output, cmd->name);
	status = check_builtins(output, cmd, prompt);
	if (status == -2)
		(*prompt)->last_status = execute_cmd(input, output, cmd, fd_tab, (*prompt)->env);
	else
	{
		printf("\nis_builtins\n");
		(*prompt)->last_status = status;
	}
}

void printf_fdtab(int **fd_tab)
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
	while (pipe_nbr + 1)
	{
		fd_tab[i] = malloc(sizeof(int) * 2);
		if (!fd_tab[i])
		{
			//free_tab((void **)fd_tab);
			return (0);
		}
		if (pipe(fd_tab[i++]) == -1)
		{
			//free_tab((void **)fd_tab);
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


int	apply_cmds(t_data *prompt)
{
	t_cmd	*cmd;
	int		input;
	int		output;
	int		**fd_tab;
	int		*k;

	k = &(int){0};
	fd_tab = 0;
	//prompt->env = envp;
	cmd = prompt->cmd;
	fd_tab = create_fd_tab(find_pipe_nb(prompt), fd_tab);
	//printf_fdtab(fd_tab);
	while (cmd->next)
	{
		input = find_input_v2(cmd, fd_tab, k, prompt->str);
		output = find_output_v2(cmd, fd_tab, k);
		//printf("input : %d\n", input);
		//printf("output : %d\n\n", output);
		fd_error(input, output);
		execute(input, output, cmd, &prompt, fd_tab);
		if (output != 1)
			close(output);
		if (input != 0)
			close(input);
		// if (open("limiter_file", O_RDONLY) != -1)
		// 	unlink("limiter_file");
		cmd = cmd->next;
	}
	return (prompt->last_status);
}