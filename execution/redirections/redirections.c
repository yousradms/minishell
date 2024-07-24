/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/20 11:10:02 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_redirect_in(t_command *cmd, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    //printf("1:[%d]\n",cmd->in);//-1094795586
    if (fd == -1)
    {
        perror("open");
        //exit(EXIT_FAILURE);
        return;
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        //perror("dup2");
        close(fd);
        // exit(EXIT_FAILURE);
        return;
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
        //exit(EXIT_FAILURE);
        return;
    }
    cmd->out = fd;
    // free(filename);//hada
    close(fd);
}

// void handle_redirections(t_command **command)
// {
//     t_command *cmd;
//     int i;
//     int j;
//     char *arg[1024];
//     int k;

//     cmd = *command;
//     while (cmd != NULL)
//     {
//         i = 0;
//         j = 0;
//         while (cmd->arg[i] != NULL)
//         {
//             if (strcmp(cmd->arg[i], "<") == 0)//detecter heredoc o ndekhelih l fd o mn l fd ghadi dupih l 0
//             {
//                 if (cmd->arg[i + 1] != NULL)
//                 {
//                     handle_redirect_in(cmd, cmd->arg[i + 1]);
//                     // free(cmd->arg[i]);
//                     // free(cmd->arg[i + 1]);
//                     i += 2; // Skip over both "<" and the filename
//                 }
//             }
//             else if (strcmp(cmd->arg[i], ">") == 0)
//             {
//                 if (cmd->arg[i + 1] != NULL) 
//                 {
//                     handle_redirect_out(cmd, cmd->arg[i + 1], 0);
//                     // free(cmd->arg[i]);
//                     i += 2; // Skip over both ">" and the filename
//                 }
//             } 
//             else if (strcmp(cmd->arg[i], ">>") == 0)
//             {
//                 if (cmd->arg[i + 1] != NULL)
//                 {
//                     handle_redirect_out(cmd, cmd->arg[i + 1], 1);
//                     // free(cmd->arg[i]);
//                     i += 2; // Skip over both ">>" and the filename
//                 }
//             }
//             //<<
//             else if(strcmp(cmd->arg[i] , "<<") == 0)
//             {
//                     dup2(cmd->my_fd, STDIN_FILENO);
//                     close(cmd->my_fd);
//                     // free(cmd->arg[i]);
//                     i += 2;
//             }
//             else
//             {
//                 arg[j++] = cmd->arg[i];
//                 i++;
//             }
//         }
//         arg[j] = NULL; // Terminate the new argument array
//         k = 0;
//         while(k < j)
//         {
//             cmd->arg[k] = arg[k];
//             k++;
//         }
//         cmd->arg[j] = NULL;
//         cmd = cmd->next;
//         // free(cmd);
//     }
//     cmd = *command;
    
    
// }
void handle_redirections(t_command *cmd)
{
    for (int i = 0; cmd->arg[i] != NULL; ++i)
    {
        if (strcmp(cmd->arg[i], ">") == 0)
        {
            handle_redirect_out(cmd,cmd->arg[i + 1],0);
            for (int j = i; cmd->arg[j] != NULL; ++j)
            {
                cmd->arg[j] = cmd->arg[j + 2];
            }
            i--; 
        } 
        else if (strcmp(cmd->arg[i], ">>") == 0)
        {
            handle_redirect_out(cmd,cmd->arg[i + 1],1);
            for (int j = i; cmd->arg[j] != NULL; ++j)
                cmd->arg[j] = cmd->arg[j + 2];
            i--;
        }
        else if (strcmp(cmd->arg[i], "<" ) == 0)
        {
            handle_redirect_in(cmd,cmd->arg[i + 1]);
            for (int j = i; cmd->arg[j] != NULL; ++j)
                cmd->arg[j] = cmd->arg[j + 2];
            i--;
        }
        else if (strcmp(cmd->arg[i], "<<" ) == 0)
        {
            dup2(cmd->my_fd, STDIN_FILENO);
            close(cmd->my_fd);
            for (int j = i; cmd->arg[j] != NULL; ++j)
                cmd->arg[j] = cmd->arg[j + 2];
            i--;
        }
    }
}

// void handle_redirections(t_command *cmd)
// {
//     for (int i = 0; cmd->arg[i] != NULL; ++i)
//     {
//         if (strcmp(cmd->arg[i], ">") == 0)
//         {
//             handle_redirect_out(cmd,cmd->arg[i + 1],0);
//             for (int j = i; cmd->arg[j] != NULL; ++j)
//             {
//                 cmd->arg[j] = cmd->arg[j + 2];
//             }
//             i--; 
//         } 
//         else if (strcmp(cmd->arg[i], ">>") == 0)
//         {
//             handle_redirect_out(cmd,cmd->arg[i + 1],1);
//             for (int j = i; cmd->arg[j] != NULL; ++j)
//                 cmd->arg[j] = cmd->arg[j + 2];
//             i--;
//         }
//         else if (strcmp(cmd->arg[i], "<" ) == 0)
//         {
//             handle_redirect_in(cmd,cmd->arg[i + 1]);
//             for (int j = i; cmd->arg[j] != NULL; ++j)
//                 cmd->arg[j] = cmd->arg[j + 2];
//             i--;
//         }
//         else if (strcmp(cmd->arg[i], "<<" ) == 0)
//         {
//             dup2(cmd->my_fd, STDIN_FILENO);
//             close(cmd->my_fd);
//             for (int j = i; cmd->arg[j] != NULL; ++j)
//                 cmd->arg[j] = cmd->arg[j + 2];
//             i--;
//         }
//     }
// }





