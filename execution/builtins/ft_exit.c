/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:41 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/06 10:28:56 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int	ft_is_number(char *s)
{
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (0);
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

void	ft_exit(t_command **command)
{
	if (!((*command)->arg[1]))
	{
		printf("exit\n");
		exit(ft_atoi(exit_s(0, 0)));
	}
	else if (!ft_is_number((*command)->arg[1]))
	{
		printf("exit\nMinishell: exit: %s: \
		numeric argument required\n", (*command)->arg[1]);
		exit(255);
	}
	else if ((*command)->arg[2])
	{
		printf("exit\nMinishell: exit: too many arguments\n");
		return ;
	}
	else
		handle_exit((*command)->arg[1]);
}
