/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:18 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/08 20:16:51 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define BUFFER_SIZE 1024
#include <string.h>

int handle_herdoc(char *delimiter, int f) 
{
    char *line;
    int temp_fd[2];
    // int my_fd = 0;
    char *s = remove_quotes(delimiter);
    if (f)// Open or create "temp.txt" for appending
    {
        unlink("temp.txt");
        temp_fd[0] = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        temp_fd[1] = open("temp.txt", O_RDONLY | O_TRUNC, 0644);
        if (temp_fd[0] == -1 || temp_fd[1] == -1)
            return (-1);
        unlink("temp.txt");
    }
    while (1)
    {
        line = readline(">");
        if (line == NULL)
            break;
        if (strncmp(line, s, strlen(s)) == 0 && line[strlen(s)] == '\0')// Check for the delimiter at the start of the line
        {
            // dup2(STDIN_FILENO, temp_fd);

            free(line);
            break; // Exit loop when delimiter is found
        }

        if (f)// Write the line and newline character to the temporary file
        {
            if (write(temp_fd[0], line, strlen(line)) == -1)
            {
                free(line);
                close(temp_fd[0]);
                // return (my_fd);
            }
            if (write(temp_fd[0], "\n", 1) == -1)
            {
                free(line);
                close(temp_fd[0]);
                // return (my_fd);
            }
        }
        free(line);
    }
    // if (f)// Close the temporary file after writing
    // {
    //     close(temp_fd);
    //     temp_fd = open("temp.txt", O_RDONLY, 0644);
    //     if (temp_fd == -1)
    //         return (0);
    //     close(temp_fd);
    // }
    return(temp_fd[1]);
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