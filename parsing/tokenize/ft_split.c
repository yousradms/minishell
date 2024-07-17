/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/04 17:08:57 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//pipe->builtins-->fork child process
//no pipe-->builtins-->dont't fork child process
//echo "${var1-${var2}}"
static void handle_quotes(char *str, char **tab, int *i, int *i2, int *i3, char *quote)
{
    while ((str[*i] > 32 || *quote) && str[*i] != '\0')
    {
        if (str[*i] == '"' && *quote == '"')
        {
            if (str[*i + 1] == '"')
            {
                tab[*i2][(*i3)++] = str[(*i)++];
                tab[*i2][(*i3)++] = str[(*i)++];
            }
            else
            {
                *quote = 0;
                tab[*i2][(*i3)++] = str[(*i)++];
            }
        }
        else if (str[*i] == '"' && *quote == 0)
        {
            *quote = '"';
            tab[*i2][(*i3)++] = str[(*i)++];
        }
        else if (str[*i] == '\'' && *quote == 0)
        {
            *quote = '\'';
            tab[*i2][(*i3)++] = str[(*i)++];
        }
        else if (str[*i] == *quote)
        {
            *quote = 0;
            tab[*i2][(*i3)++] = str[(*i)++];
        }
        else
            tab[*i2][(*i3)++] = str[(*i)++];
    }
}

static void skip_delimiters(char *str, char **tab, int *i, int *i2)
{
    if (*i > 0 && str[*i - 1] == '\x1F')
        (*i)++;
    else
    {
        while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n') && str[*i] != '\0')
        {
            tab[*i2] = malloc(sizeof(char) * 2);
            tab[*i2][0] = str[*i];
            tab[*i2][1] = '\0';
            (*i2)++;
            (*i)++;
        }
    }
}

char **ft_split(char *str)
{
    int i;
    int i2;
    int i3;
    char **tab;
    char quote;

    i = 0;
    i2 = 0;
    quote = 0;
    tab = malloc(sizeof(char *) * w_count);
    while (str[i])
    {
        if (str[i] > 32 || quote)
        {
            i3 = 0;
            tab[i2] = malloc(sizeof(char) * L_count);
            handle_quotes(str, tab, &i, &i2, &i3, &quote);
            tab[i2][i3] = '\0';
            i2++;
        }
        else if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            skip_delimiters(str, tab, &i, &i2);
        else
            i++;
    }
    tab[i2] = NULL;
    return (tab);
}
