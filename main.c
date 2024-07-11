/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/11 07:40:49 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac,char **av,char **env)
{ 
    (void)ac;
    (void)av;
    char **envp;
    char *line;
    
    envp = set_env(env);
    int i = 0;
    int j = 0;
    // i = dup(STDIN_FILENO);
    // j = dup(STDOUT_FILENO);
    while (1)
    {
        i = dup(STDIN_FILENO);
        j = dup(STDOUT_FILENO);
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
            envp = parsing_execute_command(&line, envp);
            //printf("here.......\n");
            dup2(j, STDOUT_FILENO);
            dup2(i, STDIN_FILENO);
            close(i);
            close(j);
            while (wait(NULL) != -1)
                ;
        }
        free(line);
    }

    return(0);
}
