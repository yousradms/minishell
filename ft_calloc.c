/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:47:20 by ksellami          #+#    #+#             */
/*   Updated: 2023/12/04 19:08:29 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t size)
{
	size_t			taille;
	unsigned char	*ptr;

	taille = num_elements * size;
	if (num_elements && taille / num_elements != size)
		return (NULL);
	ptr = malloc(taille);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, taille);
	return (ptr);
}
