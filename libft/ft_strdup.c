/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:11:32 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/24 12:02:53 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*duplicate;
	int		len;

	len = ft_strlen(src);
	duplicate = (char *)malloc(len + 1);
	if (duplicate == NULL)
	{
		return (NULL);
	}
	ft_strcpy(duplicate, src);
	duplicate[len] = '\0';
	return (duplicate);
}
