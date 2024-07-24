/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:18 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/24 09:31:52 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define BUFFER_SIZE 1024
#include <string.h>

void    sigint_handler_herdoc(int signo)
{
    if (signo == SIGINT)
    {
        if (waitpid(-1, 0, WNOHANG) == 0)
        {
            printf("\n");
            return;
        }
        else
            exit(1);
    }
}
static int del_without_quotes(char *s)
{
    if(s[0] != '\"' && s[0] != '\'')
        return(1);
    return(0);
}


int handle_herdoc(char *delimiter, char **env)
{
    char *line;
    int temp_fd[2];
    int flag;
    int pid;

    // Handle delimiter and flag
    flag = del_without_quotes(delimiter) ? 1 : 0;
    char *s = remove_quotes(delimiter);

    // Handle file operations
    unlink("temp.txt");
    temp_fd[0] = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    temp_fd[1] = open("temp.txt", O_RDONLY | O_TRUNC, 0644);
    if (temp_fd[0] == -1 || temp_fd[1] == -1) {
        free(s);
        return -1;
    }
    unlink("temp.txt");

    // Set up signal handlers
    signal(SIGINT, sigint_handler_herdoc);
    signal(SIGQUIT, SIG_IGN);
    rl_catch_signals = 1;

    // Fork process to read lines
    pid = fork();
    if (pid == 0)
    {
        // Child process
        while (1)
        {
            line = readline(">");
            if (line == NULL) break;

            // Check for delimiter
            if (strncmp(line, s, strlen(s)) == 0 && line[strlen(s)] == '\0') {
                free(s);
                free(line);
                break;
            }

            // Expand environment variables if flag is 1
            if (flag && contain_env(line))
            {
                char *str = strdup(line);
                set_expanded(&str, &line, env);
                free(str);
            }

            // Write to temporary file
            if (write(temp_fd[0], line, strlen(line)) == -1 || write(temp_fd[0], "\n", 1) == -1)
            {
                free(line);
                free(s);
                close(temp_fd[0]);
                return temp_fd[1];
            }
            free(line);
        }
        exit(0);
    }
    else
    {
        // Parent process
        waitpid(pid, 0, 0);
        rl_catch_signals = 0;
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, sigint_handler);
    }
    free(s);
    return temp_fd[1];
}

void handle_herddoce(t_command **command, char **env)
{
    (void)env;
    t_command *first;
    int i;

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
                    first->my_fd = handle_herdoc(first->arg[i + 1],env);  
                }
            }
            i++;
        }
        first = first->next;
    }  
}
