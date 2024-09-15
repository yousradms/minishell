/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:40:50 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/14 20:03:25 by ydoumas          ###   ########.fr       */
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

void	execute_one_command(t_command **commande, char **env)
{
	char	*full_command;
	char	*name;

	full_command = find_commande((*commande)->arg[0], env);
	if (full_command == NULL)
	{
		if ((*commande)->arg[0] != NULL)
		{
			write(2, "Minishell: ", 12);
			write(2, (*commande)->arg[0], ft_strlen((*commande)->arg[0]));
			write(2, ": command not found\n", 21);
		}
		exit(127);
	}
	if (full_command[0] == '1' || full_command[0] == '2')
		return ;
	if(full_command[0] == '3')
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n", (*commande)->arg[0]);
		return ;
	}
	name = getenv("HOME");
	// check_if_directory((*commande)->arg[0], name);
	if (execve(full_command, (*commande)->arg, env) == -1)
	{
		perror("execve");
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
