/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:41 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 10:05:51 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	out_range(char c, int sign, long num)
{
	if (c < '0' || c > '9')
		return (1);
	if (sign == 1)
	{
		if (num > (LONG_MAX - (c - '0')) / 10)
			return (1);
	}
	else
	{
		if (-num < (LONG_MIN + (c - '0')) / 10)
			return (1);
	}
	return (0);
}

int	ft_is_number(char *s)
{
	long	num;
	int		sign;

	s = ft_strtrim(s, " ");
	if (*s == '\0')
		return (0);
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (*s == '\0')
		return (0);
	num = 0;
	while (*s)
	{
		if (out_range(*s, sign, num))
			return (0);
		num = num * 10 + (*s - '0');
		s++;
	}
	return (1);
}

static void	handle_exit(char *arg)
{
	int	exit_status;

	exit_status = ft_atoi(arg);
	printf("exit\n");
	exit(exit_status);
}

static void	num_arg(char *s)
{
	ft_putstr_fd("exit\nMinishell: exit: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	ft_exit(t_command **command)
{
	if ((*command)->arg[1] && ft_strlen((*command)->arg[1]) == 0)
	{
		num_arg((*command)->arg[1]);
		exit(255);
	}
	else if (!((*command)->arg[1]))
	{
		printf("exit\n");
		exit(ft_atoi(exit_s(0, 0)));
	}
	else if ((*command)->arg[1] && !ft_is_number((*command)->arg[1]))
	{
		num_arg((*command)->arg[1]);
		exit(255);
	}
	else if ((*command)->arg[1] && (*command)->arg[2])
	{
		ft_putstr_fd("exit\nMinishell: exit: too many arguments\n", 2);
		handle_cd_error(1);
		return ;
	}
	else
		handle_exit((*command)->arg[1]);
}
