/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 14:22:51 by ksellami         ###   ########.fr       */
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
            parsing_execute_command(&line, envp);
        }
        free(line);
    }
    return(0);
}
