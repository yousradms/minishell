/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:11:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/02 21:04:50 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_for_child_process(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			perror("waitpid");
		else
			return ;
	}
	handle_exit_status(status);
}

char	**handle_builtin_command(t_command **commande, char **env)
{
	handle_redirections(*commande);
	if ((*commande)->in == -1 || (*commande)->out == -1)
		return (exit_s(1, 1), env);
	return (execute_builtin(commande, env));
}

void	handle_child_process(t_command **commande, char **env)
{
	if (g_global != 0)
	{
		close((*commande)->my_fd);
		exit(0);
	}
	handle_redirections(*commande);
	if ((*commande)->in == -1 || (*commande)->out == -1)
		exit(1);
	execute_one_command(commande, env);
	exit(0);
}

char	**execute(t_command **commande, char **env)
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
