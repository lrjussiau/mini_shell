/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:06:20 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/15 08:45:56 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	count_words(char *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i++;
			count++;
			while (s[i] && s[i] != '"' && s[i] != '\'')
				i++;
			i++;
		}
		if (s[i] != c && s[i] != '"' && s[i] != '\'' && s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}	
	return (count);
}

static	int	get_word_len(char const *s, char c, int trig)
{
	int	i;

	i = 0;
	if (trig == 1)
	{
		i++;
		while (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
		i++;
	}
	else
	{
		while (s[i] && s[i] != c)
			i++;
	}
	return (i);
}

static void	free_array(int i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static	char	**split(char const *s, char c, char **array, int words_count)
{
	int	i;
	int	j;
	int	trig;

	i = 0;
	j = 0;
	trig = 0;
	while (i < words_count)
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j] == '\'' || s[j] == '"')
			trig = 1;
		array [i] = ft_substr(s, j, get_word_len(&s[j], c, trig));
		if (!array[i])
		{
			free_array(i, array);
			return (NULL);
		}
		if (trig == 1)
		{
			trig = 0;
			j++;
			while (s[j] && s[j] != '\'' && s[j] != '"')
				j++;
			j++;
		}
		else
		{
			while (s[j] && s[j] != c)
				j++;
		}
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
	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = split(s, c, array, words);
	return (array);
}
