/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:32:32 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/04 18:55:12 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *initialize_command_line()
{
    char *line = strdup("");
    if (!line)
        return (NULL);
    return (line);
}

static char *concatenate_line_content(char *line, char *content)
{
    char *temp = line;
    line = ft_strjoin(line, content);
    free(temp);
    return (line);
}

static void initialize_split(t_node **current_node, t_command **result, t_command **new_command, char **line, t_node *head) {
    *current_node = head;
    *result = NULL;
    *new_command = NULL;
    *line = initialize_command_line();
}

int finalize_command(t_command **result, char *line)
{
    t_command *new_command;
    
    if (*line != '\0')
    {
        new_command = create_new_command(line);
        if (!new_command)
            return (0);
        add_back(result, new_command);
    }
    else
        free(line);
    return (1);
}

t_command *ft_split2(t_node **head)
{
    t_node *current_node;
    t_command *result;
    t_command *new_command;
    char *line;
    
    if (!head || !*head)
        return (NULL);
    initialize_split(&current_node, &result, &new_command, &line, *head);
    if (!line)
        return (NULL);
    while (current_node != NULL)
    {
        if (current_node->type == PIPE && current_node->state == 1)
        {
            if (!add_new_command_to_result(&result, &line))
                return (NULL);
        }
        else
            line = concatenate_line_content(line, current_node->content);
        current_node = current_node->next;
    }
    if (!finalize_command(&result, line))
        return (NULL);
    return (result);
}
