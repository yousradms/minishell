/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:25:24 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/22 19:25:19 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_one_command(t_command **command)
{
    pid_t pid;
    int status;
    
    if (command == NULL || *command == NULL)
    {
        fprintf(stderr, "No command to execute\n");
        return;
    }
    //==handle builtins==//
    //   // Check for built-in commands
    // if (is_builtin((*command)->arg[0])) {
    //     execute_builtin(command);
    //     return;
    // }
    
    //Step 1: Fork a Child Process
    pid = fork();//<0-->error =0-->child process
    //>0 parent process
    if (pid < 0)
    { 
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    { 
        //==handle signals==//
        //==handle redirections==//
        // Child process
        if (execvp((*command)->arg[0], (*command)->arg) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    { 
        // Parent process
        waitpid(pid, &status, WUNTRACED);
        //// Handle the exit status of the child process $?
    }
}


void execute(t_command **command)
{
    int nbrElem;
    
    nbrElem = count_elem_command(*command);
    //printf("The numbers of commands is : [%d]\n",nbrElem);
    if(nbrElem == 1)
        execute_one_command(command); 
    //else
        //handle pipes 
}