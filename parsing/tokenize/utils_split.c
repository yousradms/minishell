/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:27:10 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:07:50 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	handle_double_quote(char *str, char **tab, t_args1 *a)
{
	if (str[a->i + 1] == '"')
	{
		tab[a->i2][(a->i3)++] = str[(a->i)++];
		tab[a->i2][(a->i3)++] = str[(a->i)++];
	}
	else
	{
		a->quote = 0;
		tab[a->i2][(a->i3)++] = str[(a->i)++];
	}
}

void	handle_single_quote(char *str, char **tab, t_args1 *a)
{
	a->quote = '\'';
	tab[a->i2][(a->i3)++] = str[(a->i)++];
}
