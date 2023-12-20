/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:39:55 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/06 11:50:12 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int len)
{
	char			*ret_dest;
	const char		*s;
	unsigned int	i;

	i = 0;
	s = src;
	ret_dest = dest;
	if (!s && !ret_dest)
		return (NULL);
	while (i < len)
	{
		ret_dest[i] = s[i];
		i++;
	}
	return (dest);
}
