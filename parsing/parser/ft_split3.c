/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:06 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/04 18:48:23 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static void handle_quotation(char *str, char *quote, int *i)
{
    if (!*quote && (str[*i] == '\'' || str[*i] == '"'))
        *quote = str[*i];
    else if (*quote && str[*i] == *quote)
        *quote = 0;
}

static void fill_word(char *str, char *word, int *i, int *i3, char *quote)
{
    while (str[*i] && (!is_whitespace(str[*i]) || *quote))
    {
        handle_quotation(str, quote, i);
        word[(*i3)++] = str[*i];
        (*i)++;
    }
    word[*i3] = '\0';
}

static void skip_initial_whitespaces(char *str, int *i)
{
    while (is_whitespace(str[*i]))
        (*i)++;
}

char **ft_split3(char *str)
{
    int i;
    int i2;
    int i3;
    char **tab;
    char qouat;

    i = 0;
    i2 = 0;
    i3 = 0;
    qouat = 0;
    tab = malloc(sizeof(*tab) * (MAX_WORDS + 1));
    if (tab == NULL)
        return (NULL); 
    skip_initial_whitespaces(str, &i);
    while (str[i])
    {
        if (!is_whitespace(str[i]))
        {
            tab[i2] = malloc(sizeof(char) * (MAX_LENGTH + 1));
            i3 = 0;
            fill_word(str, tab[i2], &i, &i3, &qouat);
            i2++;
        }
        else
            i++;
    }
    tab[i2] = NULL; 
    return (tab);
}
