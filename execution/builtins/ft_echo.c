/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 20:41:19 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_n(char *s)
{
	if (*s == '-')
		s++;
	if (*s == '\0' || *s != 'n')
		return (0);
	while (*s && *s == 'n')
		s++;
	return (*s == '\0');
}

void	ft_echo(t_command **cmd)
{
	int		i;
	int		n_option;
	char	*ex;

	i = 1;
	n_option = 0;
	while ((*cmd)->arg[i] != NULL && check_n((*cmd)->arg[i]))
	{
		n_option++;
		i++;
	}
	while ((*cmd)->arg[i] != NULL)
	{
		ft_putstr_fd((*cmd)->arg[i], 1);
		if ((*cmd)->arg[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	ex = exit_s(0, 1);
	free(ex);
}
