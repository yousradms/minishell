/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:11:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/28 16:29:18 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_exit_status(int status)
{
    if (WIFEXITED(status)) // Check if the child exited normally
    {
        exit_s(WEXITSTATUS(status), 1); // Get the exit status
    }
    else if (WIFSIGNALED(status)) // Check if the child was terminated by a signal
    {
        int signal_number = WTERMSIG(status);
        exit_s(128 + signal_number,1);// Common practice to return 128 + signal number
    }
}


// char **handle_one_command(t_command **commande, char **env)
// {
//     int status;
//     pid_t pid;
//     char *full_command;
    
//     handle_redirections(*commande);
//     handle_quotes_ex(commande);
    
//     if (is_builtin((*commande)->arg[0]))
//     {
//         env = execute_builtin(commande, env);
//         exit_s(0,1); // Assuming built-ins are successful
//         return env;
//     }
    
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         return env;
//     }
//     else if (pid == 0)
//     {
//         full_command = find_commande((*commande)->arg[0], env);
//         if (full_command == NULL)
//         {
//             fprintf(stderr, "Minishell: %s: command not found\n", (*commande)->arg[0]);
//             exit(127);
//         }
//         if (execve(full_command, (*commande)->arg, env) == -1)
//         {
//             perror("execve");
//             free(full_command);
//             exit(127);
//         }
//         free(full_command);
//     }
//     else
//     {
//         // Wait for the child process to finish and capture its status
//         if (waitpid(pid, &status, 0) == -1)
//         {
//             perror("waitpid");
//             return env;
//         }
//         // Handle exit status
//         handle_exit_status(status);
//     }
    
//     return env;
// }
char **handle_one_command(t_command **commande, char **env)
{
    int status;
    pid_t pid;
    char *full_command;

    handle_redirections(*commande);
    handle_quotes_ex(commande);

    if (is_builtin((*commande)->arg[0]))
    {
        env = execute_builtin(commande, env);
        exit_s(0, 1); // Assuming built-ins are successful
        return env;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return env;
    }
    else if (pid == 0)
    {
        full_command = find_commande((*commande)->arg[0], env);
        if (full_command == NULL)
        {
            fprintf(stderr, "Minishell: %s: command not found\n", (*commande)->arg[0]);
            exit(127);
        }
        if (execve(full_command, (*commande)->arg, env) == -1)
        {
            perror("execve");
            free(full_command);
            exit(127);
        }
        free(full_command);
    }
    else
    {
        // Wait for the child process to finish and capture its status
        while (waitpid(pid, &status, 0) == -1)
        {
            if (errno == EINTR) {
                perror("waitpid"); // Interrupted by signal, retry waitpid
            } else {
                // perror("waitpid");
                return env;
            }
        }
        // Handle exit status
        handle_exit_status(status);
    }
    return env;
}


char **execute(t_command **commande, char **env)
{
    if (commande == NULL || *commande == NULL)
        return env;
    if (env == NULL) 
        return env;
    if((*commande)->next == NULL)
        env = handle_one_command(commande,env);  
    else
        env = handle_multiple_command(commande,env);
    return(env);
}