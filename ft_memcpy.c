/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:00:06 by ksellami          #+#    #+#             */
/*   Updated: 2023/12/06 19:43:23 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (src == dest)
		return (dest);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (const unsigned char *)src;
	while (n > 0)
	{
		*dest_ptr++ = *src_ptr++;
		n--;
	}
	return (dest);
}
