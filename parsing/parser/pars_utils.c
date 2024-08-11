/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:22:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:52:17 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int	is_whitespace(char c)//yousra
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*initialize_command_line(void)//yousra
{
	char	*line;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	return (line);
}
