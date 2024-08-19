/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:15:29 by ksellami          #+#    #+#             */
/*   Updated: 2023/12/04 19:12:25 by ksellami         ###   ########.fr       */
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

static char	*nbr_to_str(long nb)
{
	int		size;
	char	*str;
	int		i;
	char	chiffre;

	size = len_num(nb);
	str = (char *)malloc(sizeof(char) * (size + 1 + (nb < 0)));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		str[i++] = '-';
		nb = -nb;
	}
	while (size > 0)
	{
		chiffre = nb / puissance(10, size - 1) + '0';
		nb = nb % puissance(10, size - 1);
		str[i++] = chiffre;
		size--;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;

	nb = n;
	if (n == 0)
	{
		str = (char *)malloc(2);
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = nbr_to_str(nb);
	return (str);
}
