/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:40:29 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 09:57:21 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *str)
{
	size_t					i;
	int						ne;
	unsigned long long int	num;

	i = 0;
	ne = 1;
	num = 0;
	if (!str)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		ne = 1 - 2 * (str[i++] == '-');
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (ne == 1 && num > LONG_MAX / 10)
			return (-1);
		else if (ne == -1 && num > LONG_MAX / 10)
			return (0);
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * ne);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (fd >= 0)
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
}
