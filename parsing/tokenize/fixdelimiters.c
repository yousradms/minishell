/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixdelimiters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:45:33 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:07:29 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_length_adjustment(char c, char next_char)
{
	if (c == '\'' || c == '\"')
		return (4);
	if ((c == '>' && next_char == '>') || (c == '<' && next_char == '<'))
		return (2);
	if (c == '$' && next_char == '$')
		return (4);
	if (c == '|' || c == '<' || c == '>')
		return (2);
	if (c == '$')
		return (2);
	return (0);
}

static int	calculate_new_length(char *s)
{
	int		len;
	int		new_len;
	int		i;
	char	next_char;

	i = 0;
	len = ft_strlen(s);
	new_len = len;
	while (i < len)
	{
		if (i + 1 < len)
			next_char = s[i + 1];
		else
			next_char = '\0';
		new_len += get_length_adjustment(s[i], next_char);
		if ((s[i] == '>') || (s[i] == '<'))
		{
			if ((s[i] == '>' && s[i + 1] == '>') \
			|| (s[i] == '<' && s[i + 1] == '<'))
				i++;
		}
		i++;
	}
	return (new_len);
}

static void	process_double_redirect(char *s, char *new_s, int *i, int *j)
{
	add_double_delimiters(new_s, i, j, s[*i]);
	while (s[*i] && s[*i] == ' ')
		new_s[(*j)++] = s[(*i)++];
	while (s[*i] && s[*i] != ' ' && s[*i] != '<' && s[*i] != '>' \
	&& s[*i] != '|' && s[*i] != '\'' && s[*i] != '\"')
		new_s[(*j)++] = s[(*i)++];
}

static void	process_characters(char *s, char *new_s, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (s[i] == '\'')
			add_single_quote_delimiters(s, new_s, &i, &j);
		else if (s[i] == '\"')
			add_double_quote_delimiters(s, new_s, &i, &j);
		else if ((s[i] == '>' && i + 1 < len && s[i + 1] == '>') \
		|| (s[i] == '<' && i + 1 < len && s[i + 1] == '<'))
			process_double_redirect(s, new_s, &i, &j);
		else if (s[i] == '$' && i + 1 < len && s[i + 1] == '$')
			add_double_dollar_delimiters(new_s, &i, &j);
		else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			add_one_delimiters(new_s, &i, &j, s[i]);
		else if (s[i] == '$')
			add_one_delimiters_before(new_s, &i, &j, s[i]);
		else
			new_s[j++] = s[i++];
	}
	new_s[j] = '\0';
}

char	*add_delimiter(char *s)
{
	int		len;
	int		new_len;
	char	*new_s;

	len = ft_strlen(s);
	new_len = calculate_new_length(s);
	new_s = allocate_new_string(new_len);
	if (!new_s)
		return (NULL);
	process_characters(s, new_s, len);
	if (!new_s)
		return (NULL);
	return (new_s);
}
