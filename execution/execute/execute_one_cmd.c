/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:11:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/18 21:23:50 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

static void	wait_for_child_process(pid_t pid)
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

char	**handle_one_command(t_command **commande, char **env)
{
	pid_t	pid;

	if (!commande || !(*commande) || (*commande)->arg[0] == NULL)
		return (env);
	if (is_builtin((*commande)->arg[0]))
	{
		handle_redirections(*commande);
		env = execute_builtin(commande, env);
		return (env);
	}
	pid = fork_process();
	if (pid == -1)
		return (env);
	else if (pid == 0)
	{
		if (global != 0)
		{
			close((*commande)->my_fd);
			exit(0);
		}
		handle_redirections(*commande);
		execute_one_command(commande, env);
		exit(0);
	}
	else
	{
		close((*commande)->my_fd);
		wait_for_child_process(pid);
	}
	return (env);
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
