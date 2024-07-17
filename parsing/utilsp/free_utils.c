/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:14:03 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/17 17:10:07 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_commands(t_command *commands)
{
    t_command *temp;
    while (commands != NULL)
    {
        temp = commands;
        commands = commands->next;
        free(temp->cmd);

        if (temp->arg) {
            for (int i = 0; temp->arg[i] != NULL; i++) {
                free(temp->arg[i]);
            }
            free(temp->arg);
        }
        free(temp);
    }
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