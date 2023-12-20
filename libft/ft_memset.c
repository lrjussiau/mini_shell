/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:21:35 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:32 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, unsigned int len)
{
	unsigned int	i;
	char			*ret_str;

	i = 0;
	ret_str = (char *)str;
	while (len > 0)
	{
		ret_str[i] = c;
		i++;
		len--;
	}
	return (ret_str);
}
