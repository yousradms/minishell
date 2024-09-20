/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:11:12 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/20 13:12:39 by ksellami         ###   ########.fr       */
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

static char	**handle_builtin_command(t_command **commande, char **env)
{
	handle_redirections(*commande);
	if ((*commande)->in == -1 || (*commande)->out == -1)
		return (env);
	return (execute_builtin(commande, env));
}

static void	handle_child_process(t_command **commande, char **env)
{
	if (global != 0)
	{
		close((*commande)->my_fd);
		exit(0);
	}
	handle_redirections(*commande);
	if ((*commande)->in == -1 || (*commande)->out == -1)
		exit(0);
	execute_one_command(commande, env);
	exit(0);
}

char	**handle_one_command(t_command **commande, char **env)
{
	pid_t	pid;

	if (!commande || !(*commande) || (*commande)->arg[0] == NULL)
		return (env);
	if (is_builtin((*commande)->arg[0]))
		return (handle_builtin_command(commande, env));
	pid = fork_process();
	if (pid == -1)
		return (env);
	else if (pid == 0)
		handle_child_process(commande, env);
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
