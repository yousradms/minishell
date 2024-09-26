/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:48:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:08:32 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	if (fd >= 0)
	{
		ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
	}
}
