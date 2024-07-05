/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:41 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 10:17:28 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_is_number(char *s)
{
    while(*s)
    {
        if(!(*s >= '0' && *s <= '9'))
            return(0);
        s++;
    }
    return(1);
}

void ft_exit(t_command **command)
{
    int exit_status;

    if (!((*command)->arg[1]))//no arguments
    {
        printf("exit\n");
        exit(0);
    }
    else if ((*command)->arg[1])//with argument
    {
        if (!ft_is_number((*command)->arg[1]))
        {
            printf("Minishell: exit: %s: numeric argument required\n",(*command)->arg[1]);
            exit(255);
        }
        else
        {
            exit_status = atoi((*command)->arg[1]);
            if ((*command)->arg[2])
            {
                printf("Minishell: exit: too many arguments\n");
                exit(1);
            }
            else
            {
                printf("exit\n");
                exit(exit_status);
            }
        }
    }
}
