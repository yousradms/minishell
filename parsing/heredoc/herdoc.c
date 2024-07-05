/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:18 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 18:50:31 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define BUFFER_SIZE 1024
#include <string.h>

int handle_herdoc(char *delimiter, int f) 
{
    char *line;
    int temp_fd;
    int my_fd;
    char *s = remove_quotes(delimiter);
    if (f)// Open or create "temp.txt" for appending
    {
        temp_fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (temp_fd == -1)
            exit(0);
    }
    while (1)
    {
        line = readline(">");
        if (line == NULL)
            break;
        if (strncmp(line, s, strlen(s)) == 0 && line[strlen(s)] == '\0')// Check for the delimiter at the start of the line
        {
            free(line);
            break; // Exit loop when delimiter is found
        }
        if (f)// Write the line and newline character to the temporary file
        {
            if (write(temp_fd, line, strlen(line)) == -1)
            {
                free(line);
                close(temp_fd);
                exit(0);
            }
            if (write(temp_fd, "\n", 1) == -1)
            {
                free(line);
                close(temp_fd);
                exit(0);
            }
        }
        free(line);
    }
    if (f)// Close the temporary file after writing
    {
        close(temp_fd);
        temp_fd = open("temp.txt", O_RDONLY, 0644);
        if (temp_fd == -1)
            exit(0);
        my_fd = temp_fd;
        close(temp_fd);
        if (unlink("temp.txt") == -1)
            exit(0);
        return(my_fd);
    }
    return (0);
}

void handle_herddoce(t_command **command)
{
    t_command *first;
    int i;

    first = *command;
    while (first != NULL)
    {
        i = 0;
        while (first->arg[i])
        {
            if (strcmp(first->arg[i],"<<") == 0)
            {
                if (first->arg[i + 1])
                    first->my_fd = handle_herdoc(first->arg[i + 1], 1);       
            }
            i++;
        } 
        first = first->next;
    }
}