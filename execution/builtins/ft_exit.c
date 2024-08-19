/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:41 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/19 16:49:09 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int	ft_is_number(char *s)
{
	long	num;
	int		sign;

	// Trim the string of spaces
	s = ft_strtrim(s, " ");
	if (*s == '\0')
		return (0);
	
	// Handle the sign
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}

	// Check if the remaining characters are digits
	if (*s == '\0')  // No digits after the sign
		return (0);

	num = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);

		// Accumulate the number and check for overflow
		if (sign == 1)
		{
			if (num > (LONG_MAX - (*s - '0')) / 10)
				return (0);
		}
		else
		{
			if (-num < (LONG_MIN + (*s - '0')) / 10)
				return (0);
		}
		
		num = num * 10 + (*s - '0');
		s++;
	}

	// If we reach here, the number is valid
	return (1);
}

static void	handle_exit(char *arg)
{
	int	exit_status;

	exit_status = ft_atoi(arg);
	// printf("exit\n");
	write(2, "exit\n", 6);
	exit(exit_status);
}

void	ft_exit(t_command **command)
{
	if ((*command)->arg[1] && ft_strlen((*command)->arg[1]) == 0)
	{
		fprintf(stderr, "exit\nMinishell: exit: %s: \
		numeric argument required\n", (*command)->arg[1]);
		exit(255);
	}
	else if (!((*command)->arg[1]))
	{
		fprintf(stderr, "exit\n");
		exit(ft_atoi(exit_s(0, 0)));
	}
	else if (!ft_is_number((*command)->arg[1]))
	{
		fprintf(stderr, "exit\nMinishell: exit: %s: \
		numeric argument required\n", (*command)->arg[1]);
		exit(255);
	}
	else if ((*command)->arg[2])
	{
		fprintf(stderr, "exit\nMinishell: exit: too many arguments\n");
		exit_s(1, 1);
		return ;
	}
	else
		handle_exit((*command)->arg[1]);
}





