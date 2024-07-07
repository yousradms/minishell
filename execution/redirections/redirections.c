/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/07 20:27:11 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_redirect_in(t_command *cmd, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    cmd->in = fd;
    close(fd);
}

void handle_redirect_out(t_command *cmd, char *filename, int append)
{
    int flags;
    int fd;

    if (append)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else 
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    fd = open(filename, flags, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    cmd->out = fd;
    close(fd);
}

void handle_redirections(t_command **command)
{
    t_command *cmd;
    int i;
    int j;
    char *args[1024];
    int k;

    cmd = *command;
    while (cmd != NULL)
    {
        i = 0;
        j = 0;
        while (cmd->arg[i] != NULL)
        {
            if (strcmp(cmd->arg[i], "<") == 0)//detecter heredoc o ndekhelih l fd o mn l fd ghadi dupih l 0
            {
            
                if (cmd->arg[i + 1] != NULL)
                {
                    handle_redirect_in(cmd, cmd->arg[i + 1]);
                    i += 2; // Skip over both "<" and the filename
                }
                else
                {
                    fprintf(stderr, "Syntax error: Missing filename after '<'\n");
                    exit(EXIT_FAILURE);
                }
            }
            else if (strcmp(cmd->arg[i], ">") == 0)
            {
                if (cmd->arg[i + 1] != NULL) 
                {
                    handle_redirect_out(cmd, cmd->arg[i + 1], 0);
                    i += 2; // Skip over both ">" and the filename
                }
                else
                {
                    fprintf(stderr, "Syntax error: Missing filename after '>'\n");
                    exit(EXIT_FAILURE);
                }
            } 
            else if (strcmp(cmd->arg[i], ">>") == 0)
            {
                if (cmd->arg[i + 1] != NULL)
                {
                    handle_redirect_out(cmd, cmd->arg[i + 1], 1);
                    i += 2; // Skip over both ">>" and the filename
                }
                else
                {
                    fprintf(stderr, "Syntax error: Missing filename after '>>'\n");
                    exit(EXIT_FAILURE);
                }
            }
            //<<
            else if(strcmp(cmd->arg[i] , "<<") == 0)
            {
                if(cmd->arg[i + 1] != NULL)
                {
                    i += 2;
                    // printf("i'm here %d\n", cmd->my_fd);
                    //handle_heredoc_ex(cmd->my_fd , cmd->arg[ i + 1]);//here my_fd is file when we have heredoc and arg[i + 1] is delimiter
                    // dup2(cmd->my_fd, STDIN_FILENO);
                    // close(cmd->my_fd);
                }
            }
            else
            {
                args[j++] = cmd->arg[i];
                i++;
            }
        }
        args[j] = NULL; // Terminate the new argument array
        k = 0;
        while(k < j)
        {
            cmd->arg[k] = args[k];
            k++;
        }
        cmd->arg[j] = NULL;
        cmd = cmd->next;
    }
}


