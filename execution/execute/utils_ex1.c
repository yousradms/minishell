/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:03:21 by ydoumas           #+#    #+#             */
/*   Updated: 2024/09/21 14:42:36 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	check_access_errors(t_command *cmd, const char *full_command)
{
	if (cmd->arg[0] && access(full_command, F_OK) == 0 \
	&& opendir(full_command) != NULL)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->arg[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	if (cmd->arg[0] && access(full_command, X_OK) != 0)
	{
		if (access(full_command, F_OK) == 0)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(cmd->arg[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
		else
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(cmd->arg[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			// exit(127);
			// exit_s(1, 1);
			exit(1);
		}
	}
}

static void	setup_child_process(int input_fd, int fd[2], t_command *cmd)
{
	if (g_global != 0)
	{
		close((cmd)->my_fd);
		exit(0);
	}
	dup2(input_fd, STDIN_FILENO);
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
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
	*input_fd = fd[0];
}

static void	handle_fork_error(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	perror("minishell:fork");
	exit(1);
}

char	**process_pipe(t_command *cmd, char **env, pid_t *pids)
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
			handle_fork_error(fd);
		else if (pids[i] == 0)
		{
			setup_child_process(input_fd, fd, cmd);
			env = execute_command(cmd, env);
			exit(0);
		}
		else
			setup_parent_process(&input_fd, fd, cmd->my_fd);
		cmd = cmd->next;
		i++;
	}
	return (env);
}
