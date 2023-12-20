/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:11:38 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/06 11:51:49 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_word(int n)
{
	unsigned int	len;
	unsigned int	nb;

	len = 1;
	if (n < 0)
	{
		nb = -n;
		len ++;
	}
	else
		nb = n;
	while (nb > 9)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static char	*assign_str(unsigned int nb, int len, int neg, char *str)
{
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (neg == 1)
		str[0] = '-';
	while (nb != 0)
	{
		str[len - 1] = (nb % 10) + '0';
		len --;
		nb /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	nb;
	unsigned int	neg;
	char			*str;

	len = 0;
	neg = 0;
	if (n < 0)
	{
		nb = -n;
		neg = 1;
	}
	else
		nb = n;
	len += len_word(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	str = assign_str(nb, len, neg, str);
	return (str);
}
