/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixdelimiters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:45:33 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/01 20:01:20 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
// #\x1F
static void add_single_quote_delimiters(char *s, char *new_s, int *i, int *j)
{
    new_s[(*j)++] = '\x1F';
    new_s[(*j)++] = ' ';
    new_s[(*j)++] = '\'';
    (*i)++;
    while (s[*i] != '\'') {
        new_s[(*j)++] = s[(*i)++];
    }
    new_s[(*j)++] = '\'';
    new_s[(*j)++] = '\x1F';
    new_s[(*j)++] = ' ';
    (*i)++;
}

static void add_double_quote_delimiters(char *s, char *new_s, int *i, int *j)//hadi
{
    new_s[(*j)++] = '\x1F';
    new_s[(*j)++] = ' ';
    new_s[(*j)++] = '\"';
    (*i)++;
    while (s[*i] != '\"') {
        new_s[(*j)++] = s[(*i)++];
    }
    new_s[(*j)++] = '\"';
    new_s[(*j)++] = '\x1F';
    new_s[(*j)++] = ' ';
    (*i)++;
}

static void add_one_delimiters(char *s, char *new_s, int *i, int *j, char c)
{
    (void)s;
    new_s[(*j)++] = ' ';
    new_s[(*j)++] = c;
    new_s[(*j)++] = ' ';
    (*i)++;
}

static void add_one_delimiters_before(char *s, char *new_s, int *i, int *j, char c)
{
    (void)s;
    new_s[(*j)++] = '\x1F';
    new_s[(*j)++] = ' ';
    new_s[(*j)++] = c;
    (*i)++;
}

static void add_double_delimiters(char *s, char *new_s, int *i, int *j, char c1, char c2)
{
    (void)s;
    new_s[(*j)++] = ' ';
    new_s[(*j)++] = c1;
    new_s[(*j)++] = c2;
    new_s[(*j)++] = ' ';
    (*i) += 2;
}
// handle correctly delimiters when we have double quotes inside double quotes
char *add_delimiter(char *s)
{
    int len = strlen(s);
    int new_len = len;

    // Calculate the new length
    for (int i = 0; i < len; i++) {
        if (s[i] == '\'') {
            new_len += 4;
        } else if (s[i] == '\"') {

            new_len += 4 ;
        } else if (s[i] == '|' || s[i] == '<' || s[i] == '>') {
            new_len += 2;
        } else if (s[i] == '>' && i + 1 < len && s[i + 1] == '>') {
            new_len += 2;
            i++;
        } else if (s[i] == '<' && i + 1 < len && s[i + 1] == '<') {
            new_len += 2;
            i++;
        } else if (s[i] == '$' && i + 1 < len && s[i + 1] == '?') {
            new_len += 2;
            i++;
        } else if (s[i] == '$') {
            new_len += 1;
        }
    }

    // Allocate new string with enough space
    char *new_s = (char *)malloc(new_len + 1);
    if (!new_s) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int i = 0, j = 0;
    while (i < len)
    {
        if (s[i] == '\'') {
            add_single_quote_delimiters(s, new_s, &i, &j);
        } else if (s[i] == '\"') {
            add_double_quote_delimiters(s, new_s, &i, &j);
        } else if (s[i] == '|') {
            add_one_delimiters(s, new_s, &i, &j, s[i]);
        } else if (s[i] == '>' && i + 1 < len && s[i + 1] == '>') {
            add_double_delimiters(s, new_s, &i, &j, s[i], s[i + 1]);
        } else if (s[i] == '<' && i + 1 < len && s[i + 1] == '<') {
            add_double_delimiters(s, new_s, &i, &j, s[i], s[i + 1]);
        } else if (s[i] == '<' || s[i] == '>') {
            add_one_delimiters(s, new_s, &i, &j, s[i]);
        } else if (s[i] == '$' && s[i + 1] == '?') {
            add_double_delimiters(s, new_s, &i, &j, s[i], s[i + 1]);
        } else if (s[i] == '$') {
            add_one_delimiters_before(s, new_s, &i, &j, s[i]);
        } else {
            new_s[j++] = s[i++];
        }
    }
    new_s[j] = '\0';
    return new_s;
}

