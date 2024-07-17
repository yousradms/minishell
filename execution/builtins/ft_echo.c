/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 10:39:23 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_n(char *s)
{
    if (*s == '-')
        s++;
    if(*s == '\0' || *s != 'n')
        return(0);
    while (*s && *s == 'n')
        s++;
    return (*s == '\0');
}

void ft_echo(t_command **cmd)
{
    int i;
    int n_option;
    
    i = 1;
    n_option = 0;
    while ((*cmd)->arg[i] != NULL && check_n((*cmd)->arg[i]))
    {
        n_option++;
        i++;
    }
    while ((*cmd)->arg[i] != NULL)
    {
        printf("%s", (*cmd)->arg[i]);
        if ((*cmd)->arg[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (!n_option)
        printf("\n");
    // You better use write instead of printf :)
}
