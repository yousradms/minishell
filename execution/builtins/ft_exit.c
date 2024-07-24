/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:41 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/24 17:28:12 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#include "libft/libft.h"
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
        exit(ft_atoi(exit_s(0, 0)));
    }
    else if ((*command)->arg[1])//with argument
    {
        if (!ft_is_number((*command)->arg[1]))
        {
            printf("exit\n");
            printf("Minishell: exit: %s: numeric argument required\n",(*command)->arg[1]);
            exit(255);
        }
        else
        {
            exit_status = atoi((*command)->arg[1]);
            if ((*command)->arg[2])
            {
                printf("exit\n");
                printf("Minishell: exit: too many arguments\n");
                //exit(1);
                return ;
            }
            else
            {
                printf("exit\n");
                exit(exit_status);
            }
        }
    }
}
