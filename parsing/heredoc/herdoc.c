/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:18 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/17 17:13:54 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define BUFFER_SIZE 1024
#include <string.h>
static int del_without_quotes(char *s)
{
    if(s[0] != '\"' && s[0] != '\'')
        return(1);
    return(0);
}

// Handle heredoc function
int handle_herdoc(char *delimiter, int f, int *flag) 
{
    char *line;
    int temp_fd[2];
    // int my_fd = 0;

    // If delimiter does not have quotes, set flag to 1
    if(del_without_quotes(delimiter))
        *flag = 1;
    else
        *flag = 0;

    char *s = remove_quotes(delimiter);
    if (f) // Open or create "temp.txt" for appending
    {
        unlink("temp.txt");
        temp_fd[0] = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        temp_fd[1] = open("temp.txt", O_RDONLY | O_TRUNC, 0644);
        if (temp_fd[0] == -1 || temp_fd[1] == -1)
            return -1;
        unlink("temp.txt");
    }
    while (1)
    {
        line = readline(">");
        if (line == NULL)
            break;
        if (strncmp(line, s, strlen(s)) == 0 && line[strlen(s)] == '\0') // Check for the delimiter at the start of the line
        {
            free(line);
            break; // Exit loop when delimiter is found
        }

        if (f) // Write the line and newline character to the temporary file
        {
            if (write(temp_fd[0], line, strlen(line)) == -1)
            {
                free(line);
                close(temp_fd[0]);
                return temp_fd[1];
            }
            if (write(temp_fd[0], "\n", 1) == -1)
            {
                free(line);
                close(temp_fd[0]);
                return temp_fd[1];
            }
        }
        free(line);
    }
    return temp_fd[1];
}
//expand inside the file where i have herdoc
// static void expand_her(int fd, char **env)
// {
//     //char buffer[1024];
//     //int bytesRead;
//     char *line = NULL;
//     size_t len = 0;
//     ssize_t read;
//     FILE *file = fdopen(fd, "r");

//     if (file == NULL)
//     {
//         perror("Error opening file descriptor");
//         return;
//     }

//     while ((read = getline(&line, &len, file)) != -1)
//     {
//         if (contain_env(line))
//         {
//             char *str = NULL;
//             str = strdup(line);
//             set_expanded(&str, &line, env);
//             free(str);
//         }
//         printf("%s", line);
//     }

//     if (line)
//     {
//         free(line);
//     }

//     fclose(file);
// }
//expand inside the file where i have herdoc
// static void expand_her(int fd, char **env)
// {
//     char buffer[1024];
//     ssize_t bytes_read;
//     char *line = NULL;
//     size_t line_size = 0;

//     while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
//     {
//         buffer[bytes_read] = '\0';
//         char *start = buffer;
//         char *end;

//         while ((end = strchr(start, '\n')))
//         {
//             *end = '\0';
//             if (contain_env(start))
//             {
//                 char *str = strdup(start);
//                 set_expanded(&str, &line, env);
//                 if (line)
//                 {
//                     printf("%s\n", line);
//                     free(line);
//                     line = NULL;
//                     line_size = 0;
//                 }
//             }
//             else
//             {
//                 printf("%s\n", start);
//             }
//             start = end + 1;
//         }

//         if (start[0] != '\0')
//         {
//             size_t remaining = strlen(start);
//             line = realloc(line, line_size + remaining + 1);
//             strcpy(line + line_size, start);
//             line_size += remaining;
//         }
//     }

//     if (line)
//     {
//         printf("%s\n", line);
//         free(line);
//     }

//     close(fd);
// }
//
//here
void expand_her(int fd, char **env)
{
    // (void)env;
    // Variables
    char *line = NULL;
    char buffer[1024];
    ssize_t bytesRead;

    // Read lines from file descriptor using readline
    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytesRead] = '\0';

        char *start = buffer;
        char *newline_pos;
        
        while ((newline_pos = strchr(start, '\n')) != NULL)
        {
            *newline_pos = '\0';
            line = strdup(start);
            //printf("%s\n",line);
            if (contain_env(line))
            {
                char *str = strdup(line);
                set_expanded(&str, &line, env);
                free(str);
            }
            printf("%s\n", line);
            
                free(line);

            start = newline_pos + 1;
        }
    }

    if (bytesRead == -1)
    {
        perror("Error reading from file descriptor");
    }
}



// Handle heredoc command function
void handle_herddoce(t_command **command, char **env)
{
    (void)env;
    t_command *first;
    int i;
    int flag;

    first = *command;
    while (first != NULL)
    {
        i = 0;
        while (first->arg[i])
        {
            if (strcmp(first->arg[i], "<<") == 0)
            {
                if (first->arg[i + 1])
                {
                    first->my_fd = handle_herdoc(first->arg[i + 1], 1, &flag);
                    //printf("[%d]----[%d]\n", first->my_fd, flag);
                    if(flag)
                    {
                        //printf("Must expand what inside this file\n");
                        expand_her(first->my_fd, env);
                    }
                }  
            }
            i++;
        }
        first = first->next;
    }
}