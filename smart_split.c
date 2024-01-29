/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:06:20 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/29 18:09:18 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	count_words(char *s, char c, int count, int i)
{
	char	current_quote;

	current_quote = 0;
	while (s[++i])
	{
		if ((s[i] == '"' || s[i] == '\'') && current_quote == 0)
		{
			current_quote = s[i];
			count++;
		}
		else if (s[i] == current_quote)
			current_quote = 0;
		else if (current_quote == 0 && s[i] != c)
		{
			count++;
			while (s[i] != c)
			{
				i++;
				if (s[i + 1] == '\0')
					break ;
			}
		}
	}
	return (count);
}

static int	get_word_len(char const *s, char c)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (s[i] && (current_quote || s[i] != c))
	{
		if ((s[i] == '"' || s[i] == '\'') && current_quote == 0)
			current_quote = s[i];
		else if (s[i] == current_quote)
			current_quote = 0;
		i++;
	}
	return (i);
}

static int	advance_index(char const *s, int *j, char c)
{
	char	current_quote;

	current_quote = 0;
	while (s[*j] && (current_quote || s[*j] != c))
	{
		if ((s[*j] == '"' || s[*j] == '\'') && current_quote == 0)
			current_quote = s[*j];
		else if (s[*j] == current_quote)
			current_quote = 0;
		(*j)++;
	}
	return (*j);
}

static char	**split(char const *s, char c, char **array, int words_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (s[j] && s[j] == c)
			j++;
		array[i] = ft_substr(s, j, get_word_len(&s[j], c));
		if (!array[i])
		{
			free_array(i, array);
			return (NULL);
		}
		advance_index(s, &j, c);
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_smart_split(char *s, char c)
{
	char	**array;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c, 0, -1);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	return (split(s, c, array, words));
}
