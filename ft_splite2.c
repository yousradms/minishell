/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:32:32 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/24 17:58:51 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **fill_arg(char *str)
// {
//     char **tab;

//     tab = NULL;
//     tab = ft_split3(str);
//     return (tab);
// }

// Function to add a command node to the back of the list
void add_back(t_command **head, t_command *new_node)
{
    if (!head || !new_node) {
        return;
    }

    if (*head == NULL) {
        *head = new_node;
    } else {
        t_command *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}
t_command *ft_split2(t_node **head)
{
    if (!head || !*head) {
        return NULL;
    }

    t_node *current_node = *head;
    t_command *result = NULL;
    t_command *new_command = NULL;
    char *line = strdup("");
    if (!line) {
        return NULL;
    }

    while (current_node != NULL) {
        if (current_node->type == PIPE && current_node->state == 1) {
            new_command = (t_command *)malloc(sizeof(t_command));
            if (!new_command) {
                free(line);
                return NULL;
            }
            new_command->cmd = line;
            //check redirections
            //fill arg
            new_command->arg = ft_split3(line);
            new_command->next = NULL;
            add_back(&result, new_command);

            line = strdup("");
            if (!line) {
                return NULL;
            }
        } else {
            char *temp = line;
            line = ft_strjoin(line, current_node->content);
            free(temp);
        }
        current_node = current_node->next;
    }

    if (*line != '\0') {
        new_command = (t_command *)malloc(sizeof(t_command));
        if (!new_command) {
            free(line);
            return NULL;
        }
        new_command->cmd = line;
        new_command->arg = ft_split3(line);
        new_command->next = NULL;
        add_back(&result, new_command);
    } 
    else {
        free(line);
    }

    return result;
}