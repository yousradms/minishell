/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:06 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:51:41 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

static void	handle_quotation(char *str, t_args *a)//yousra
{
	if (!a->quoat && (str[a->i] == '\'' || str[a->i] == '"'))
		a->quoat = str[a->i];
	else if (a->quoat && str[a->i] == a->quoat)
		a->quoat = 0;
}

static void	fill_word(char *str, char *word, t_args *a)//yousra
{
	while (str[a->i] && (!is_whitespace(str[a->i]) || a->quoat))
	{
		handle_quotation(str, a);
		word[(a->i3)++] = str[a->i];
		(a->i)++;
	}
	word[a->i3] = '\0';
}

static void	skip_initial_whitespaces(char *str, t_args *a)//yousra
{
	while (is_whitespace(str[a->i]))
		(a->i)++;
}

static t_args	*init_args(void)//yousra
{
	t_args	*a;

	a = malloc(sizeof(t_args));
	if (a)
	{
		a->i = 0;
		a->i2 = 0;
		a->i3 = 0;
		a->quoat = 0;
	}
	return (a);
}

char	**ft_split3(char *str)//yousra
{
	char	**tab;
	t_args	*a;

	a = init_args();
	if (!a)
		return (NULL);
	tab = malloc(sizeof(*tab) * (MAX_WORDS + 1));
	if (tab == NULL)
		return (free(a), NULL);
	skip_initial_whitespaces(str, a);
	while (str[a->i])
	{
		if (!is_whitespace(str[a->i]))
		{
			tab[a->i2] = malloc(sizeof(char) * (MAX_LENGTH + 1));
			if (!tab[a->i2])
				return (free(a), NULL);
			a->i3 = 0;
			fill_word(str, tab[a->i2], a);
			a->i2++;
		}
		else
			a->i++;
	}
	return (tab[a->i2] = NULL, free(a), tab);
}
