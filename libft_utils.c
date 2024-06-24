/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:30 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/23 14:45:05 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(*s)
    {
        i++;
        s++;
    }
    return(i);
}

int just_spaces(char *s)
{
    while(*s)
    {
        if(*s != ' ' && *s != '\t')
            return(0);
        s++;
    }
    return(1);
}

t_state get_state(char *s)
{
    if (s[0] == '"')//and closed
    {
        //s[1] not space
        return (DQ);
    }
    else if (s[0] == '\'')
        return (SQ);
    else
        return (GENERAL);
}

void free_arg(char **result)
{
    int i;

    i = 0;
    if (result)
    {
        while (result[i])
        {
            free(result[i]);
            i++;
        }
        free(result);
    }
}