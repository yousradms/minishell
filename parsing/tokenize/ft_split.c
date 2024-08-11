/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:52:48 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

static void	handle_character(char *str, char **tab, t_args1 *a)//yousra
{
	tab[a->i2][(a->i3)++] = str[(a->i)++];
}

static void	handle_quotes(char *str, char **tab, t_args1 *a)//yousra
{
	while ((str[a->i] > 32 || a->quote) && str[a->i] != '\0')
	{
		if (str[a->i] == '"' && a->quote == '"')
			handle_double_quote(str, tab, a);
		else if (str[a->i] == '"' && a->quote == 0)
		{
			a->quote = '"';
			handle_character(str, tab, a);
		}
		else if (str[a->i] == '\'' && a->quote == 0)
			handle_single_quote(str, tab, a);
		else if (str[a->i] == a->quote)
		{
			a->quote = 0;
			handle_character(str, tab, a);
		}
		else
			handle_character(str, tab, a);
	}
}

static void	skip_delimiters(char *str, char **tab, t_args1 *a)//yousra
{
	if (a->i > 0 && str[a->i - 1] == '\x1F')
		(a->i)++;
	else
	{
		while ((str[a->i] == ' ' || str[a->i] == '\t' \
		|| str[a->i] == '\n') && str[a->i] != '\0')
		{
			tab[a->i2] = malloc(sizeof(char) * 2);
			if (!tab[a->i2])
				return ;
			if (tab[a->i2] == NULL)
			{
				free_tab(tab, a->i2);
				return ;
			}
			tab[a->i2][0] = str[a->i];
			tab[a->i2][1] = '\0';
			(a->i2)++;
			(a->i)++;
		}
	}
}

static void	handle_word(char *str, char **tab, t_args1 *a)//yousra
{
	a->i3 = 0;
	tab[a->i2] = malloc(sizeof(char) * L_COUNT);
	if (tab[a->i2] == NULL)
	{
		free_tab(tab, a->i2);
		return ;
	}
	handle_quotes(str, tab, a);
	tab[a->i2][a->i3] = '\0';
	a->i2++;
}

char	**ft_split(char *str)//yousra
{
	t_args1	*a;
	char	**tab;

	a = (t_args1 *)malloc(sizeof(t_args1));
	if (!a)
		return (NULL);
	a->i = 0;
	a->i2 = 0;
	a->quote = 0;
	tab = malloc(sizeof(char *) * W_COUNT);
	if (tab == NULL)
		return (free(a), NULL);
	while (str[a->i])
	{
		if (str[a->i] > 32 || a->quote)
			handle_word(str, tab, a);
		else if (str[a->i] == ' ' || str[a->i] == '\t' || str[a->i] == '\n')
			skip_delimiters(str, tab, a);
		else
			a->i++;
	}
	return (tab[a->i2] = NULL, free(a), tab);
}
