/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:01:29 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:03:43 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[i] == '\0')
	{
		return ((char *)(str));
	}
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		while (str[i + j] == to_find[j] && (i + j) < n)
		{
			if (to_find[j + 1] == '\0')
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

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

char	*ft_strtrim(char *s1, char *set)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	n;

	n = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start >= n)
	{
		ptr = (char *)malloc(1);
		if (ptr == NULL)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (len > n - start)
		len = n - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
