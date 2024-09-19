/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:40:50 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/18 21:27:47 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	check_if_directory(char *cmd, char *name)
{
	if (!strncmp(cmd, name, strlen(name)))
	{
		// write(2, "Minishell: ", 11);
		// write(2, cmd, strlen(cmd));
		// write(2, ": is a directory\n", 18);
		exit(126);
	}
}

// void	execute_one_command(t_command **commande, char **env)
// {
// 	char	*full_command;

// 	full_command = find_commande((*commande)->arg[0], env);
// 	if (full_command == NULL)
// 	{
// 		if ((*commande)->arg[0] != NULL)
// 		{
// 			write(2, "Minishell: ", 12);
// 			write(2, (*commande)->arg[0], ft_strlen((*commande)->arg[0]));
// 			write(2, ": command not found\n", 21);
// 			exit(127);
// 		}
		
// 	}
// 	if ((*commande)->arg[0] && access((*commande)->arg[0], F_OK) == 0 && opendir((*commande)->arg[0]) != NULL)
// 	{
// 			fprintf(stderr, "Minishell: %s: is a directory\n", (*commande)->arg[0]);
// 			exit(126);
// 	}
// 	if((*commande)->arg[0] && access((*commande)->arg[0], X_OK) == 0 && opendir((*commande)->arg[0]) == NULL)
// 	{
// 		fprintf(stderr, "Minishell: %s: No such file or directory\n", (*commande)->arg[0]);
// 		exit(127);
		
// 	}
// 	if (execve(full_command, (*commande)->arg, env) == -1)
// 	{
// 		perror("Minishell: execve");
// 		exit(127);
// 	}
// 	free(full_command);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void execute_one_command(t_command **commande, char **env)
{
    char *full_command;

    full_command = find_commande((*commande)->arg[0], env);
    if (full_command == NULL)
    {
        if ((*commande)->arg[0] != NULL)
        {
            write(2, "Minishell: ", 12);
            write(2, (*commande)->arg[0], ft_strlen((*commande)->arg[0]));
            write(2, ": command not found\n", 21);
            exit(127);
        }
        return ;
    }
    if ((*commande)->arg[0] && access(full_command, F_OK) == 0 && opendir(full_command) != NULL)
    {
        fprintf(stderr, "Minishell: %s: is a directory\n", (*commande)->arg[0]);
        exit(126);
    }
    if ((*commande)->arg[0] && access(full_command, X_OK) != 0)
    {
        if (access(full_command, F_OK) == 0)
        {
            fprintf(stderr, "Minishell: %s: Permission denied\n", (*commande)->arg[0]);
            exit(126);
        }
        else
        {
            fprintf(stderr, "Minishell: %s: No such file or directory\n", (*commande)->arg[0]);
            exit(127);
        }
    }
    if (execve(full_command, (*commande)->arg, env) == -1)
    {
        perror("Minishell: execve");
        exit(127);
    }
    free(full_command);
}

void	print_cmd_not_found(char *s)
{
	write(2, "Minishell: ", 12);
	write(2, s, ft_strlen(s));
	write(2, ": command not found\n", 21);
	exit(127);
}

void	wait_for_all_processes(pid_t *pids, int cmd_count)
{
	int	j;
	int	status;

	j = 0;
	while (j < cmd_count)
	{
		waitpid(pids[j], &status, 0);
		handle_exit_status(status);
		j++;
	}
}
