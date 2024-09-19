/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:56:00 by ydoumas           #+#    #+#             */
/*   Updated: 2024/09/18 21:26:37 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

static char	**execute_command(t_command *cmd, char **env)
{
	char	*full_command;
	char	*name;

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
	name = getenv("HOME");
	check_if_directory(cmd->arg[0], name);
	if (execve(full_command, cmd->arg, env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (env);
}

static void	setup_child_process(int input_fd, int fd[2], t_command *cmd)
{
	if (global != 0)
	{
		close((cmd)->my_fd);
		exit(0);
	}
	dup2(input_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (input_fd != 0)
		close(input_fd);
	handle_redirections(cmd);
	if (!cmd || cmd->arg[0] == NULL)
		return ;
}

static void	setup_parent_process(int *input_fd, int fd[2], int fd3)
{
	close(fd3);
	close(fd[1]);
	if (*input_fd != 0)
		close(*input_fd);
	*input_fd = fd[0];//
}

static char	**process_pipe(t_command *cmd, char **env, pid_t *pids)
{
	int	fd[2];
	int	input_fd;
	int	i;

	input_fd = 0;
	i = 0;
	while (cmd)
	{
		if (cmd->next != NULL && pipe(fd) == -1)
			return (free(pids), env);
		pids[i] = fork();
		if (pids[i] < 0)
		{
			close(fd[0]);
			close(fd[1]);
			perror("minishell:fork");
			exit (1);
		}	
		else if (pids[i] == 0)
		{
			setup_child_process(input_fd, fd, cmd);
			env = execute_command(cmd, env);
			exit(0);
		}
		else
			setup_parent_process(&input_fd, fd,cmd->my_fd);
		cmd = cmd->next;
		i++;
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
