/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_delimiters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:37:17 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/18 18:23:51 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	add_single_quote_delimiters(char *s, char *new_s, int *i, int *j)
{
	new_s[(*j)++] = '\x1F';
	new_s[(*j)++] = ' ';
	new_s[(*j)++] = '\'';
	(*i)++;
	while (s[*i] != '\0' && s[*i] != '\'')
		new_s[(*j)++] = s[(*i)++];
	new_s[(*j)++] = '\'';
	new_s[(*j)++] = '\x1F';
	new_s[(*j)++] = ' ';
	(*i)++;
}

void	add_double_quote_delimiters(char *s, char *new_s, int *i, int *j)
{
	new_s[(*j)++] = '\x1F';
	new_s[(*j)++] = ' ';
	new_s[(*j)++] = '\"';
	(*i)++;
	while (s[*i] !='\0' && s[*i] != '\"')
		new_s[(*j)++] = s[(*i)++];
	new_s[(*j)++] = '\"';
	new_s[(*j)++] = '\x1F';
	new_s[(*j)++] = ' ';
	(*i)++;
}

void add_double_dollar_delimiters(char *new_s, int *i, int *j)
{
	new_s[(*j)++] = '\x1F';
	new_s[(*j)++] = ' ';
	new_s[(*j)++] = '$';
	new_s[(*j)++] = '$';
	new_s[(*j)++] = '\x1F';
	new_s[(*j)++] = ' ';
	(*i) += 2;
	
}