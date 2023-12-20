/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:10:05 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/06 11:49:48 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, unsigned int len)
{
	char			*dst;
	const char		*source;
	unsigned int	i;

	dst = dest;
	source = src;
	i = 0;
	if (!dst & !source)
		return (NULL);
	if (source < dst)
	{
		while (i++ < len)
			dst[len - i] = source[len - i];
	}
	else
	{
		while (len -- > 0)
			*(dst ++) = *(source ++);
	}
	return (dest);
}
