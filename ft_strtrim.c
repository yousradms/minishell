/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:54:52 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/13 13:29:29 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extrat_word(int debut, int fin, char *newstr, const char *s1)
{
	int	k;

	if (debut > fin)
	{
		newstr = (char *)malloc(1);
		if (newstr == NULL)
			return (NULL);
		newstr[0] = '\0';
		return (newstr);
	}
	newstr = (char *)malloc(sizeof(char) * (fin - debut + 2));
	if (newstr == NULL)
		return (NULL);
	k = 0;
	while (debut <= fin)
		newstr[k++] = s1[debut++];
	newstr[k] = '\0';
	return (newstr);
}

char	*ft_strtrim(char  *s1, char  *set)
{
	int		debut;
	int		fin;
	char	*newstr;

	newstr = NULL;
	if (s1 == NULL || set == NULL)
		return (NULL);
	debut = 0;
	fin = ft_strlen(s1) - 1;
	while (s1[debut] != '\0' && ft_strchr(set, s1[debut]))
		debut++;
	while (fin >= 0 && ft_strchr(set, s1[fin]))
		fin--;
	return (extrat_word(debut, fin, newstr, s1));
}
