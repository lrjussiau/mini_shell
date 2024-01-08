/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:52:50 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/08 09:50:55 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_pipe(char *str, t_cmd *cmd)
{
	char	**strs;
	int		i;

	strs = ft_split(str, ' ');
	i = 0;
	while (strs[i] != NULL)
	{
		if (ft_strnstr(strs[i], ">>", ft_strlen(strs[i])) != 0)
			i += get_fd_append(strs, i, cmd);
		else if (ft_strnstr(strs[i], ">", ft_strlen(strs[i])) != 0)
			i += get_fd_output(strs, i, cmd);
		if (ft_strnstr(strs[i], "<", ft_strlen(strs[i])) != 0)
			i += get_fd_input(strs, i, cmd);
		else if (ft_strnstr(strs[i], "<<", ft_strlen(strs[i])) != 0)
			printf("input limiter\n");
		if (!is_inout(strs[i]) && strs[i][0] != '\0')
			i += get_cmd(strs, i, cmd);
		i++;
	}
	ft_free_tab(strs);
}

void parse_input(char *str, t_data *data)
{
	char	**strs;
	int		i;
	t_cmd	*current;

	data = init_data(0);
	current = data->cmd;
	data->str = ft_strdup(str);
	strs = ft_split(str, '|');
	i = 0;
	while (strs[i] != NULL)
	{
		process_pipe(strs[i], current);
		i++;
		if (strs[i] != NULL)
			current->is_pipe = true;
		append_cmd(data);
		current = current->next;
	}
	ft_free_tab(strs);
	data->nb_pipe = (i - 1);
	print_data(data); //ici sera l'execute
	ft_free_input(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		n;
	t_data	*data;

	if (argc != 1)
		return (0);
	argv = NULL;
	n = 0;
	data = init_data(1);
	init_env(data, envp);
	while (n != 1)
	{
		input = readline("Mini Shell > ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		if (ft_strnstr(input, "exit", ft_strlen(input)) != 0)
		{
			n = 1;
			free(input);
			break ;
		}
		parse_input(input, data);
		free(input);
	}
	ft_free_input(data);
	ft_free_env(data);
	clear_history();
}
// TO DO LIST :
// 	- Gestion Varriable env (Lundi)
//	- Gestion Erreur (Lundi)
//  - Gestion Signal (Lundi)


//	- Gestion '' et "" -> Voir les implication (Mardi ??)
		// "" Est une str qui interprete les signe $, \n ...
		// '' Est une str qui redonne exactement la phrase donne 
//
// QUESTION :
//	- Gestion Limiter -> Doit on faire le heredoc> ??
// 	- Historique -> Gestion historique, cree un nouveau fd ? puis le unlink ?