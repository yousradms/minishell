/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:28:55 by ksellami          #+#    #+#             */
/*   Updated: 2023/12/03 19:12:10 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_chaine;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	new_chaine = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (new_chaine == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new_chaine[i] = f(i, s[i]);
		i++;
	}
	new_chaine[i] = '\0';
	return (new_chaine);
}
