/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:57:40 by ksellami          #+#    #+#             */
/*   Updated: 2023/12/06 19:12:44 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int c, size_t size )
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (((unsigned char *)memoryBlock)[i] == (unsigned char)c)
			return ((void *)((unsigned char *)memoryBlock + i));
		i++;
	}
	return (NULL);
}
