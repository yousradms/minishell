/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:11:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/08 18:09:15 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **handle_one_command(t_command **commande,char **env)
{
    pid_t pid;
    char *full_command;
    
    handle_redirections(commande);
    handle_quotes_ex(commande);
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
        full_command = find_commande((*commande)->arg[0], env);
        if (full_command == NULL)
        {
            //fprintf(stderr, "Error: find_commande returned NULL\n");
            printf("Minishell: %s: command not found\n",(*commande)->arg[0]);
            exit(EXIT_FAILURE);
        }
        if (execve(full_command, (*commande)->arg, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }   
    }
    else
        waitpid(pid, 0, 0);
    return(env);
             
}

char **execute(t_command **commande, char **env)
{

    if((*commande)->next == NULL)
        env = handle_one_command(commande,env);  
    else
        env = handle_multiple_command(commande,env);

    return(env);
}