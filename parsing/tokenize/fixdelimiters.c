/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixdelimiters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:45:33 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/10 17:13:00 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

static int	calculate_new_length(char *s)
{
	int	len;
	int	new_len;
	int	i;

	len = ft_strlen(s);
	new_len = len;
	i = 0;
	while (i < len)
	{
		if (s[i] == '\'' || s[i] == '\"')
			new_len += 4;
		else if ((s[i] == '>' && i + 1 < len && s[i + 1] == '>')
			|| (s[i] == '<' && i + 1 < len && s[i + 1] == '<'))
		{
			new_len += 2;
			i++;
		}
		else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			new_len += 2;
		else if (s[i] == '$')
			new_len += 2;
		i++;
	}
	return (new_len);
}

static char	*allocate_new_string(int new_len)
{
	char	*new_s;

	new_s = (char *)malloc(new_len + 1);
	if (!new_s)
		return (NULL);
	return (new_s);
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
			add_double_delimiters(new_s, &i, &j, s[i]);
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
	process_characters(s, new_s, len);
	if (!new_s)
		return (NULL);
	return (new_s);
}
