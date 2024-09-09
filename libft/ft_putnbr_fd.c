/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:59:48 by ksellami          #+#    #+#             */
/*   Updated: 2023/12/06 19:02:02 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static long	puissance(int nb, int p)
{
	if (p == 0)
		return (1);
	if (p > 0)
		return ((long)nb * puissance(nb, p - 1));
	return (0);
}

static int	len_num(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
	{
		return (1);
	}
	if (nb < 0)
	{
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb ;
	char	chiffre;
	int		size;

	nb = n;
	size = len_num(nb);
	if (fd < 0)
		return ;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	while (size > 0)
	{
		chiffre = nb / puissance(10, size - 1) + '0';
		nb = nb % puissance(10, size - 1);
		write(fd, &chiffre, 1);
		size--;
	}
}
