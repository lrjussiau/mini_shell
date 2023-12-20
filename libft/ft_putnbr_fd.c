/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:41:04 by ljussiau          #+#    #+#             */
/*   Updated: 2023/12/06 11:45:55 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	n;
	char			digit;

	if (nb < 0)
	{
		write(fd, "-", 1);
		n = -nb;
	}
	else
		n = nb;
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	digit = n % 10 + '0';
	write(fd, &digit, 1);
}
