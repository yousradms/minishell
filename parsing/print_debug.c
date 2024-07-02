/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:00:05 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/01 20:04:54 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_list(t_node *head)
{
    t_node *temp = head;
    
    while(temp != NULL)
    {
        printf("content is :[%s]     ",temp->content);
        printf("type is :[%d]    ",temp->type);
        printf("state is :[%d]   \n",temp->state);
        temp = temp->next;
    }
}

void print_list2(t_command *commands)
{
    t_command *cmd = commands;
    while (cmd) {
        printf("Command: %s\n", cmd->cmd);
        int l = 0;
        while (cmd->arg[l]) {
            printf("Arguments are :\n");
            printf("%s\n", cmd->arg[l]);
            l++;
        }
        cmd = cmd->next;
    }
}

void print_darg(char **s)
{
    int i = 0;
    while(s[i])
    {
        printf("[%s]\n",s[i]);
        i++;
    }
}



