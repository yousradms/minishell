/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:11:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/29 16:28:33 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

void execute_one_command(t_command **commande, char **env)
{
	char *full_command;

	full_command = find_commande((*commande)->arg[0], env);
	if (full_command == NULL)
	{
		printf("Minishell: %s: command not found\n", (*commande)->arg[0]);
		exit(127);
	}
	if (execve(full_command, (*commande)->arg, env) == -1)
	{
		perror("execve");
		exit(127);
	}
	free(full_command);
}

pid_t fork_process()
{
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

static void wait_for_child_process(pid_t pid)
{
    int status;
	
    while (waitpid(pid, &status, 0) == -1)
	{
        if (errno == EINTR)
            perror("waitpid");
        else
            return ;
    }
    handle_exit_status(status);
}

char **handle_one_command(t_command **commande, char **env)
{
	pid_t pid;

	handle_redirections(*commande);
	if (is_builtin((*commande)->arg[0]))
	{
		env = execute_builtin(commande, env);
		exit_s(0,1);
		return (env);
	}
	pid = fork_process();
	if (pid == -1)
		return (env);
	else if (pid == 0)
		execute_one_command(commande, env);
	else
		wait_for_child_process(pid);
	return (env);       
}

char **execute(t_command **commande, char **env)
{
	if (commande == NULL || *commande == NULL)
		return (env);
	if (env == NULL) 
		return (env);
	if ((*commande)->next == NULL)
		env = handle_one_command(commande, env);  
	else
		env = handle_multiple_command(commande, env);
	return (env);
}
