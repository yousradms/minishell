/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:17:50 by ksellami          #+#    #+#             */
/*   Updated: 2023/12/04 19:19:23 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == (char)searchedChar)
		{
			return ((char *)(string + i));
		}
		i++;
	}
	if ((char)searchedChar == '\0')
		return ((char *)(string + i));
	return (NULL);
}
