/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:30 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 14:29:41 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin(char *s1, char *s2)
{
    if (!s1 || !s2)
        return NULL;
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = (char *)malloc(len1 + len2 + 1);
    if (!result) return NULL;
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
