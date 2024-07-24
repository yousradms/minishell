/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:11:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/24 13:57:32 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int global_exit_status = 0;
// int handle_exit_status(int status)
// {
//     int exit_code = 0;
//     int signal_number;

//     if (WIFEXITED(status)) // Check if the child exited normally
//     {
//         exit_code = WEXITSTATUS(status); // Get the exit status
//         printf("Command exited with status: %d\n", exit_code);
//     }
//     else if (WIFSIGNALED(status)) // Check if the child was terminated by a signal
//     {
//         signal_number = WTERMSIG(status);
//         printf("Command terminated by signal: %d\n", signal_number);
//         exit_code = 128 + signal_number; // Common practice to return 128 + signal number
//     }
//     return exit_code;
// }

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
//         global_exit_status = 0; // Assuming built-ins are successful
//         return env;
//     }
    
//     pid = fork_process();
//     if (pid == -1)
//     {
//         perror("fork");
//         global_exit_status = 1; // Set exit status to 1 on fork error
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
//             global_exit_status = 1; // Set exit status to 1 on waitpid error
//             return env;
//         }
//         // Handle exit status
//         global_exit_status = handle_exit_status(status >> 8);
//     }
    
//     return env;
// }
int global_exit_status = 0;

int handle_exit_status(int status)
{
    int exit_code = 0;

    if (WIFEXITED(status)) // Check if the child exited normally
    {
        exit_code = WEXITSTATUS(status); // Get the exit status
    }
    else if (WIFSIGNALED(status)) // Check if the child was terminated by a signal
    {
        int signal_number = WTERMSIG(status);
        exit_code = 128 + signal_number; // Common practice to return 128 + signal number
    }
    return exit_code;
}


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
        global_exit_status = 0; // Assuming built-ins are successful
        return env;
    }
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        global_exit_status = 1; // Set exit status to 1 on fork error
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
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            global_exit_status = 1; // Set exit status to 1 on waitpid error
            return env;
        }
        // Handle exit status
        global_exit_status = handle_exit_status(status);
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