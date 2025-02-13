/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:40:50 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/10 20:00:21 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_one_command(t_command **commande, char **env)
{
	char	*full_command;

	full_command = find_commande((*commande)->arg[0], env);
	if (full_command == NULL)
	{
		if ((*commande)->arg[0] != NULL)
			print_cmd_not_found((*commande)->arg[0]);
		return ;
	}
	check_access_errors(*commande, full_command);
	if (execve(full_command, (*commande)->arg, env) == -1)
	{
		perror("Minishell: execve");
		exit(127);
	}
	free(full_command);
}

void	print_cmd_not_found(char *s)
{
	char	*ex;

	write(2, "Minishell: ", 12);
	write(2, s, ft_strlen(s));
	write(2, ": command not found\n", 21);
	ex = exit_s(127, 1);
	free(ex);
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

char	**handle_one_command(t_command **commande, char **env)
{
	pid_t	pid;

	if (!commande || !(*commande) || (*commande)->arg[0] == NULL)
		return (env);
	if (is_builtin((*commande)->arg[0]))
		return (handle_builtin_command(commande, env));
	pid = fork();
	if (pid == -1)
		return (perror("Minishell : fork"), env);
	else if (pid == 0)
		handle_child_process(commande, env);
	else
	{
		close((*commande)->my_fd);
		wait_for_child_process(pid);
	}
	return (env);
}

void	update_directories(t_env **envp, char *oldpwd, char *cwd)
{
	update_oldpwd(envp, oldpwd);
	update_pwd(envp, cwd);
}
