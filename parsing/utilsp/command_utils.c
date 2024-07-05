/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:50:16 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/04 20:18:56 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void add_back(t_command **head, t_command *new_node)
{
    t_command *current;
    
    if (!head || !new_node)
        return;
    if (*head == NULL)
        *head = new_node;
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

t_command *create_new_command(char *line)
{
    t_command *new_command = (t_command *)malloc(sizeof(t_command));
    if (!new_command)
    {
        free(line);
        return (NULL);
    }
    new_command->cmd = line;
    new_command->arg = ft_split3(line);
    new_command->next = NULL;
    return (new_command);
}

int add_new_command_to_result(t_command **result, char **line)
{
    t_command *new_command;
    
    new_command = create_new_command(*line);
    if (!new_command)
        return 0;
    add_back(result, new_command);
    *line = initialize_command_line();
    if (!(*line))
        return (0);
    return (1);
}