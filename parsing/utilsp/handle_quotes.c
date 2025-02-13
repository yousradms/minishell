/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:14 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:08:06 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quot(char *line, char a, char b)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == b)
			while (line[++i] != b)
				if (!line[i])
					return (0);
		if (line[i] == a)
		{
			while (line[++i] != a)
				if (!line[i])
					return (0);
		}
	}
	return (1);
}

char	*remove_quotes(char *s)
{
	char	*token;
	int		i;
	int		j;

	token = malloc(ft_strlen(s) + 1);
	if (!token)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i++;
		else
			token[j++] = s[i++];
	}
	token[j] = '\0';
	return (token);
}
