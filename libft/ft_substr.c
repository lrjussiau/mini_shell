/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:14:47 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/06 11:47:14 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char			*new_str;
	unsigned int	i;
	unsigned int	j;

	new_str = (char *)malloc(len + 1);
	if (!s || !(new_str))
		return (0);
	i = start;
	j = 0;
	while (i < (unsigned int)ft_strlen(s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}
