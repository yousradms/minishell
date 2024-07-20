/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/20 12:22:01 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


pid_t g_pid = 0;  
int g_status = 0; // Global status


void prompt(void) {
    write(1, "minishell🥶😁 ", 12); // Ajout d'un espace pour séparer le prompt de l'entrée utilisateur
    fflush(stdout); // S'assurer que le buffer est vidé
}

// Function to handle signals sent to the process
void process(int sign_num) {
    if (sign_num == SIGQUIT) {
        write(1, "Quit: 3\n", 8);
        g_status = 131;
    } else if (sign_num == SIGINT) {
        write(1, "\n", 1);
        g_status = 130;
        prompt(); // Afficher le prompt après avoir reçu SIGINT
    }
}

// Signal handler function
void sigint_handler(int sign_num) {
    if (sign_num == SIGINT) {
        if (g_pid == 0) {
            // For the main process
            rl_on_new_line(); // Move to a new line
            rl_replace_line("", 0); // Clear the current line
            // write(1,"",1);
            write(1, "\n", 1); // Write a newline character
            prompt(); // Display the prompt
            g_status = 1;
        } else {
            process(sign_num); // Handle SIGINT in child processes
        }
    } else if (sign_num == SIGQUIT) {
        process(sign_num); // Handle SIGQUIT
    }
}
int main(int ac,char **av,char **env)
{ 
    (void)ac;
    (void)av;
    char **envp;
    char *line;
    
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigint_handler);
    envp = set_env(env);
    int i = 0;
    int j = 0;
    // i = dup(STDIN_FILENO);
    // j = dup(STDOUT_FILENO);
    while (1)
    {
        line = readline("minishell🥶😁");
        if (!line)         
            exit(1);
        if (line[0] == '\0' || just_spaces(line))
        {
            free(line);
            continue;
        }
        if (strlen(line) > 0)
        {
            add_history(line);
            i = dup(STDIN_FILENO);
            j = dup(STDOUT_FILENO);
            envp = parsing_execute_command(&line, envp);

            dup2(j, STDOUT_FILENO);
            dup2(i, STDIN_FILENO);
            close(i);
            close(j);
            while (wait(NULL) != -1)
                ;
        }
        free(line);
    }
    // Free envp

    return(0);
}
