/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:18 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/21 20:01:16 by ydoumas          ###   ########.fr       */
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

// Handle heredoc function
int handle_herdoc(char *delimiter, int f, int *flag) 
{
    char *line;
    int temp_fd[2];
    
    if (del_without_quotes(delimiter)) {
        if (flag)
            *flag = 1;
    } else {
        if (flag)
            *flag = 0;
    }
        
    char *s = remove_quotes(delimiter);
    
    if (f) {
        temp_fd[0] = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        temp_fd[1] = open("temp.txt", O_RDONLY, 0644);
        if (temp_fd[0] == -1 || temp_fd[1] == -1) {
            close(temp_fd[0]);
            close(temp_fd[1]);
            return -1;
        }
    }

    signal(SIGINT, sigint_handler_herdoc);
    signal(SIGQUIT, SIG_IGN);
    rl_catch_signals = 1;
    int pid = fork();
    if (pid == 0) {
        while (1) {
            line = readline(">");
            if (line == NULL)
                break;
            if (strncmp(line, s, strlen(s)) == 0 && line[strlen(s)] == '\0') {
                free(s);
                free(line);
                break;
            }
            if (f) {
                if (write(temp_fd[0], line, strlen(line)) == -1) {
                    free(line);
                    free(s);
                    close(temp_fd[0]);
                    close(temp_fd[1]);
                    exit(EXIT_FAILURE);
                }
                if (write(temp_fd[0], "\n", 1) == -1) {
                    free(line);
                    free(s);
                    close(temp_fd[0]);
                    close(temp_fd[1]);
                    exit(EXIT_FAILURE);
                }
            }
            free(line);
        }
        close(temp_fd[0]);
        exit(0);
    } else {
        waitpid(pid, NULL, 0);
        rl_catch_signals = 0;
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, sigint_handler);
    }
    
    close(temp_fd[0]);
    return temp_fd[1];
}

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
            //printf("%s\n", line);
            
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
    int flag =0;


    first = *command;
    while (first != NULL)
    {
        i = 0;
        
        while (first->arg[i])
        {
            if (strcmp(first->arg[i], "<<") == 0)
            // handle_redirections(command);
            {
                if (first->arg[i + 1])
                {
                    first->my_fd = handle_herdoc(first->arg[i + 1], 1, &flag);
                    //printf("[%d]----[%d]\n", first->my_fd, flag);
                    if(flag)
                    {
                        // printf("Must expand what inside this file\n");
                        expand_her(first->my_fd, env);
                    }
                }
            }
            i++;
        }
        first = first->next;
    }
    
}