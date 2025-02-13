/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:40:01 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:07:45 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_one_delimiters(char *new_s, int *i, int *j, char c)
{
	new_s[(*j)++] = ' ';
	new_s[(*j)++] = c;
	new_s[(*j)++] = ' ';
	(*i)++;
}

void	add_one_delimiters_before(char *new_s, int *i, int *j, char c)
{
	new_s[(*j)++] = '\x1F';
	new_s[(*j)++] = ' ';
	new_s[(*j)++] = c;
	(*i)++;
}

void	add_double_delimiters(char *new_s, int *i, int *j, char c1)
{
	new_s[(*j)++] = ' ';
	new_s[(*j)++] = c1;
	new_s[(*j)++] = c1;
	new_s[(*j)++] = ' ';
	(*i) += 2;
}
