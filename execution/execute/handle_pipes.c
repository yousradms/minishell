/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:56:00 by ydoumas           #+#    #+#             */
/*   Updated: 2024/09/21 14:51:39 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

char	**execute_command(t_command *cmd, char **env)
{
	char	*full_command;

	if (is_builtin(cmd->arg[0]))
	{
		execute_builtin(&cmd, env);
		return (env);
	}
	if (!cmd || cmd->arg[0] == NULL)
		return (env);
	full_command = find_commande(cmd->arg[0], env);
	if (full_command == NULL)
		print_cmd_not_found(cmd->arg[0]);
	check_access_errors(cmd, full_command);
	// printf("Was there\n");
	if (execve(full_command, cmd->arg, env) == -1)
	{
		perror("Minishell: execve");
		exit(EXIT_FAILURE);
	}
	return (env);
}

char	**handle_multiple_command(t_command **commande, char **env)
{
	pid_t	*pids;
	int		cmd_count;

	cmd_count = count_nbr_commands(*commande);
	pids = (pid_t *)malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (NULL);
	env = process_pipe(*commande, env, pids);
	wait_for_all_processes(pids, cmd_count);
	return (free(pids), env);
}
