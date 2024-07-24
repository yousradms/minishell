/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:11:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/22 17:51:31 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **handle_one_command(t_command **commande,char **env)
{
    pid_t pid;
    char *full_command;
    //handle_quotes_ex(commande);

    handle_redirections(*commande);//leaks here
    if (is_builtin((*commande)->arg[0]))
    {
        env = execute_builtin(commande, env);
        return(env) ;
    }
    pid = fork_process();
    if (pid == -1)
        return (env);
    else if (pid == 0)
    {
        // print_list2(*commande);
        // exit(1);
        full_command = find_commande((*commande)->arg[0], env);
        // printf("[%s]\n",full_command);
        // exit(1);
        if (full_command == NULL)
        {
            printf("Minishell: %s: command not found\n",(*commande)->arg[0]);
            exit(EXIT_FAILURE);
        }
        if (execve(full_command, (*commande)->arg, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
        free(full_command);  
    }
    else
        waitpid(pid, 0, 0);
    
    return(env);
             
}

char ** execute(t_command **commande, char **env)
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