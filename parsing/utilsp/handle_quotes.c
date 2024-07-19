/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:14 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/17 18:49:25 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quot(char *line, char a, char b)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == b)
			while (line[++i] != b)
				if (!line[i])
					return (0);
		if (line[i] == a)
		{
			while (line[++i] != a && line[i]);
			if (line[i] != a)
				return (0);
		}
	}
	return (1);
}

char *remove_quotes(char *s)
{
    char *token;
    int i;
    int j;

    token = malloc(strlen(s) + 1);
    if(!token)
        return(NULL);
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

char *remove_dquotes(char *s)
{
    char *token;
    int i;
    int j;

    token = malloc(strlen(s) + 1);
    if(!token)
        return(NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == '"')
            i++;
        else
            token[j++] = s[i++];
    }
    token[j] = '\0';
    return (token);
}

char *remove_squotes(char *s)
{
    char *token;
    int i;
    int j;

    token = malloc(strlen(s) + 1);
    if(!token)
        return(NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            i++;
        else
            token[j++] = s[i++];
    }
    token[j] = '\0';
    return (token);
}

