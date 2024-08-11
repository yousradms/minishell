/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:14 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/10 17:18:41 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

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

char	*remove_dquotes(char *str)
{
	int		len;
	char	*result;
	int		j;
	int		k;
	int		double_quote_open;

	len = ft_strlen(str);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	j = 0;
	k = 0;
	double_quote_open = 0;
	while (str[j])
	{
		if (str[j] == '\"')
			double_quote_open = !double_quote_open;
		else
			result[k++] = str[j];
		j++;
	}
	result[k] = '\0';
	return (result);
}

char	*remove_squotes(char *str)
{
	int		len;
	char	*result;
	int		j;
	int		k;
	int		single_quote_open;

	len = ft_strlen(str);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	j = 0;
	k = 0;
	single_quote_open = 0;
	while (str[j])
	{
		if (str[j] == '\'')
			single_quote_open = !single_quote_open;
		else
			result[k++] = str[j];
		j++;
	}
	result[k] = '\0';
	return (result);
}
