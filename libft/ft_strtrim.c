/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:10:10 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/06 11:47:08 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_check_char(char const *set, char c)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	end;
	unsigned int	start;
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s1 || *s1 == '\0')
		return (ft_strdup(""));
	end = ft_strlen((char *)s1) - 1;
	start = 0;
	while (s1[start] != '\0' && ft_check_char(set, s1[start]) != 0)
		start++;
	while (ft_check_char(set, s1[end]) != 0 && end > 0)
		end--;
	if (end == 0)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(end - start + 2);
	if (!str)
		return (0);
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
