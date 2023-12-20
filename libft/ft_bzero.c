/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:21:35 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/06 11:52:30 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *str, unsigned int len)
{
	char	*ret_str;

	ret_str = str;
	while (len > 0)
	{
		*ret_str = '\0';
		ret_str ++;
		len --;
	}
	return (ret_str);
}
