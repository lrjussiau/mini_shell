/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:04:59 by vvuadens          #+#    #+#             */
/*   Updated: 2023/12/28 12:01:04 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


/*fonctionnement execution (questionnable)*/

/*- pour chaque cmd->pour chaque input i de cette commande->executer la commande avec input i
 - accumuler l'output dans un fichier temporaire
 - si cmd est la derniere alors copie fichier temp dans on output associé (au final copie dans 1 seul output (le dernier)pas tous)
 -si cmd n'est pas derniere alors copie fichier temp dans on output associé et crée un nouveau input pour prochaine cmd et copie temp dans nouveau input
 ...*/


/*todo*/

/*appel aux 2 exec changer appel apr ref-> de prompt a &prompt*/

/*fd_printf(int fd, char *str, ...)*/

/*modify cmd->option[i] with appropriate i when called in builtins-> bc option[0] = cmd  etc*/


//check the validity of fd
void	fd_error(int input, int output)
{
	if (input == -1 || output == -1)
	{
		printf("Error opening file(update output)");
		ft_clean();
		exit (-1);
	}
}

//copy the string placed affter the limiter
void	copy_limiter_str(int file_fd, t_data prompt)
{
	char	limiter;
	char	**str;

	i = 0;
	find_limiter(prompt->str, &limiter);
	while (str != limiter[0])
	{
		if (!(ft_strncmp(str, limiter, ft_strlen(limiter))))
		{
			while ((ft_strncmp(str + 1, limiter, ft_strlen(limiter))))
				write(file_fd, &str[0], 1);
			return ;
		}
		str++;
	}
}

//find limiter
void	find_limiter(char *str, char *limiter)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (!(str[i] == '<' && str[i + 1] == '<'))
		i++;
	while (str[i] == ' ')
		i++;
	j = i;
	while ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
		i++;
	limiter = malloc(sizeof(char) * (i - j + 1));
	if (!limiter)
	{
		printf("Malloc error");
		ft_clean();
		exit(-1);
	}
	while (j < i)
		limiter[k++] = str[j++];
	limiter[j] = '\0';
}


//choose the appropriate input format
int	find_input(t_cmd **cmd, t_data prompt)
{
	int	input;

	if ((*cmd)->input->is_fd)
	{
		input = open((*cmd)->name, O_RDONLY);
	}
	else if((*cmd)->input->is_limiter)
	{
		input = open(limiter_file, O_RDWR | O_CREAT, 0644);
		fd_error(input, 0);
		copy_limiter_str(input, prompt);
	}
	else
	{
		input = STDIN;
	}
	return (input);
}

//chosse appropriate output format
int	find_output(t_cmd **cmd)
{
	int	fd;

	while (!((*cmd)->next))
			*cmd = (*cmd)->next;
	if ((*cmd)->is_fd)
	{
		if ((*cmd)->output->is_append)
			fd = open((*cmd)->output->name, O_WRONLY | O_APPEND);
		else
			fd = open((*cmd)->output->name, O_WRONLY | O_CREAT, 0644);
	}
	else
		fd = STDOUT;
	fd_error(fd, NULL);
}

//execute a command 
void	execute_cmd(int input, int output, t_cmd cmd, t_data **prompt)
{
	pid_t	child;
	input	fd[2];

	fd[0] = input;
	fd[1] = output;
	if (pipe(fd) == -1)
	{
		ft_clean();
		printf("Error piping fd");
		exit (-1);
	}
	child = fork();
	if (child == 0)
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		(*prompt)->last_status = execve(cmd->name, cmd->options, (*prompt)->env);
	}
	else if (child > 0)
		return ;
	else
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
}

//execute a cat on a temporary file ->copy content
void	tmp_exec(int input, int output, t_data **prompt)
{
	//fd[] in fork(possible?) sinon leak sinon cre \e avant
	pid_t	child;
	input	fd[2];

	fd[0] = input;
	fd[1] = output;
	if (pipe(fd) == -1)
	{
		ft_clean();
		printf("Error piping fd");
		exit (-1);
	}
	child = fork();
	if (child == 0)
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		(*prompt)->last_status = execve("/bin/cat", {"cat", NULL}, (*prompt)->env);
	}
	else if (child > 0)
		return ;
	else
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
}

//add new input to the next command inputs
void	add_input(t_cmd **cmd)
{
	t_inout	*input;
	t_inout	*new_node;

	input = (*cmd)->next->input;
	while (input)
		input = input->next;
	new_node = init_inout();
	if (!new_node)
	{
		printf("Error creating new_node");
		exit (-1);
	}
	new_node->is_fd = true;
	new_node->name = "tmp_input";
	new_node->next = NULL;
	input->next = new_node;
}

//copy temporary output in cmd output
//if more cmd temporary output also copied into new input added to next cmd
void	update_output(t_cmd **cmd, t_data *prompt)
{
	int	input;
	int	output;

	input = open("tmp_file", O_RDONLY);
	output = find_output(cmd);
	fd_error(input, output);
	tmp_exec(input, output, &prompt);
	close(input);
	close(output);
	if ((*cmd)->next)
	{
		add_input(cmd);
		input = open("tmp_file", O_RDONLY);
		output = open("tmp_input", O_WRONLY | O_CREAT, 0644);
		fd_error(input, output);
		tmp_exec(input, output, &prompt);
		close(input);
		close(output);
	}
	//unlink("tmp_file")
}

//execute the commands
void	apply_cmds(t_data prompt)
{
	t_cmd	*cmd;
	t_inout	*input;
	int		input;
	int		output;

	cmd = prompt.cmd;
	while (cmd)
	{
		input = prompt.input;
		while (input)
		{
			input = find_input(&cmd, prompt);
			output = open("tmp_file", O_CREAT | O_WRONLY | O_APPEND);
			fd_error(input, output);
			execute_cmd(input, output, cmd, &prompt);
			close(output);
			close(input);
			input = input->next;
			cmd->input = cmd->input->next;
		}
		update_output(&cmd, &prompt);
		cmd = cmd->next;
	}
}
