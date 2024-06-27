/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:57:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/26 20:49:35 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_error(t_node **head)
{
    (void)head;
    printf("Error\n");
    return (1);
}

void parsing(t_node **head)
{

    t_node *temp = *head;
    t_node *last = ft_lstlast(*head);
    if(temp->type == 2)
    {
        if (temp->state == 1 )
        {
            ft_error(head);
            return;
        }
        else
            return;
    }
    if (last->type == 2 || last->type == 3 || last->type == 4 || last->type == 5 || last->type == 6)
    {
        if(last->state == 1)
        {
            ft_error(head);
            return ;
        }
        else
            return ;
    }   
    while(temp != NULL)
    {
        // if(temp->type == 6 && temp->state == 1)
        // {
        //     if(temp->next)
        //         handle_herddoc(temp);
        // }
        if((temp->type == 3 || temp->type == 4 || temp->type == 5 || temp->type == 6) && temp->next->type != 9)
        {
            if(temp->state == 1)
            {
                ft_error(head);
                return;
            }

        }   
        if(temp->type == 2 && temp->next->type == 2)
        {
            if(temp->state == 1)
            {
                ft_error(head);
                return;
            }
           
        }   
        temp = temp->next;
    }  
}