/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:40:01 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/04 16:41:00 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void add_one_delimiters(char *s, char *new_s, int *i, int *j, char c)
{
    (void)s;
    new_s[(*j)++] = ' ';
    new_s[(*j)++] = c;
    new_s[(*j)++] = ' ';
    (*i)++;
}

void add_one_delimiters_before(char *s, char *new_s, int *i, int *j, char c)
{
    (void)s;
    new_s[(*j)++] = '\x1F';
    new_s[(*j)++] = ' ';
    new_s[(*j)++] = c;
    (*i)++;
}

void add_double_delimiters(char *s, char *new_s, int *i, int *j, char c1, char c2)
{
    (void)s;
    new_s[(*j)++] = ' ';
    new_s[(*j)++] = c1;
    new_s[(*j)++] = c2;
    new_s[(*j)++] = ' ';
    (*i) += 2;
}