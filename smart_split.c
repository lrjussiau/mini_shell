/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:06:20 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/11 08:50:21 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// static int	count_words(char const *s, char c)
// {
// 	size_t	count;
// 	int		in_quote;
// 	size_t	i;

// 	count = 0;
// 	i = 0;
// 	in_quote = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '"')
// 		{
// 			if (in_quote == 0)
// 				in_quote = 1;
// 			else
// 				in_quote = 0;
// 		}
// 		if (s[i] != c)
// 		{
// 			count++;
// 			while (s[i] && s[i] != c)
// 				i++;
// 		}
// 		else if (s[i] == c)
// 			i++;
// 	}
// 	return (count);
// }
// cat "2 f" fr

int	count_words(char *s, char c)
{
	int		count;
	int		i;
	bool	in_quote;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i++;
			count++;
			while (s[i] && s[i] != '"')
				i++;
		}
		if (s[i] != c && s[i] != '"' && s[i] != '\'')
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

// static	size_t	get_word_len(char const *s, char c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] && s[i] != c)
// 		i++;
// 	return (i);
// }

// static void	free_array(size_t i, char **array)
// {
// 	while (i > 0)
// 	{
// 		i--;
// 		free(array[i]);
// 	}
// 	free(array);
// }

// static	char	**split(char const *s, char c, char **array, size_t words_count)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (i < words_count)
// 	{
// 		while (s[j] && s[j] == c)
// 			j++;
// 		array [i] = ft_substr(s, j, get_word_len(&s[j], c));
// 		if (!array[i])
// 		{
// 			free_array(i, array);
// 			return (NULL);
// 		}
// 		while (s[j] && s[j] != c)
// 			j++;
// 		i++;
// 	}
// 	array[i] = NULL;
// 	return (array);
// }

// char	**ft_smart_split(char const *s, char c)
// {
// 	char	**array;
// 	size_t	words;

// 	if (!s)
// 		return (NULL);
// 	words = count_words(s, c);
// 	array = (char **)malloc(sizeof(char *) * (words + 1));
// 	if (!array)
// 		return (NULL);
// 	array = split(s, c, array, words);
// 	return (array);
// }

int main(void)
{
	printf("%d\n", count_words("cat \"ok test\" deux", ' '));
	// printf("%d\n", );
}