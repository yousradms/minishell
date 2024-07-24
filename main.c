/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/24 15:21:02 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_s(int new_one, int set)
{
    static int x = 0;
    if (set == 1)
        x = new_one;
    else
        return x;
    return 0;
}

void    sigint_handler(int signo)
{
    int    i;

    if (signo == SIGINT)
    {
        i = wait(NULL);
        
        if (i <= 0)
        {
            printf("\n");
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
            exit_s(1, 1);
        }
        else
            printf("\n");
    }
    else if (signo == SIGQUIT)
    {
        if (waitpid(-1, 0, WNOHANG) == 0)
        {
            printf("Quit: 3\n");
        }
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
    rl_catch_signals = 0;
    envp = set_env(env);
    int i = 0;
    int j = 0;
    // i = dup(STDIN_FILENO);
    // j = dup(STDOUT_FILENO);
    while (1)
    {
        line = readline("minishell🥶😁");
        if (!line)
        {
            
            printf("exit\n");
            exit(0);
        }         
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
