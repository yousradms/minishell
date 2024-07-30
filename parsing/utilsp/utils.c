/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:26:44 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/25 21:06:25 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

int just_spaces(char *s)
{
	while(*s)
	{
		if (*s != ' ' && *s != '\t')
			return (0);
		s++;
	}
	return (1);
}

t_state get_state(char *s)
{
	if (s[0] == '"')
		return (DQ);
	else if (s[0] == '\'')
		return (SQ);
	else
		return (GENERAL);
}
