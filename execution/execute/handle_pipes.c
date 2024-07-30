/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:56:00 by ydoumas           #+#    #+#             */
/*   Updated: 2024/07/29 16:24:32 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

static  char **execute_command(t_command *cmd, char **env)
{
	char *full_command;

	if (is_builtin(cmd->arg[0]))
	{
		execute_builtin(&cmd, env);
		return (env);
	}
	if (!cmd)
		return (env);
	full_command = find_commande(cmd->arg[0], env);
	if (full_command == NULL)
	{
		fprintf(stderr,"Minishell: %s: command not found\n",cmd->arg[0]);
		exit_s(127, 1);
		exit(127);
	}
	if (execve(full_command, cmd->arg, env) == -1)
	{
		perror("execve");
		exit_s(EXIT_FAILURE, 1);
		exit(EXIT_FAILURE);
	}
	return(env);
}

static void wait_for_all_processes(pid_t *pids, int cmd_count)
{
    int j;
    int status;

    j = 0;
    while (j < cmd_count)
    {
        waitpid(pids[j], &status, 0);
        if (WIFEXITED(status))
            exit_s(WEXITSTATUS(status), 1);
        j++;
    }
}

static void setup_child_process(int input_fd, int fd[2], t_command *cmd)
{
    dup2(input_fd, STDIN_FILENO);
    if (cmd->next)
        dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    if (input_fd != 0)
        close(input_fd);
    handle_redirections(cmd);
}

static void setup_parent_process(int *input_fd, int fd[2])
{
    close(fd[1]);
    if (*input_fd != 0)
        close(*input_fd);
    *input_fd = fd[0];
}

static char **process_pipe(t_command *cmd, char **env, pid_t *pids)
{
    int fd[2];
    int input_fd;
    int i;

	input_fd = 0;
	i = 0;
    while (cmd)
	{
        if (cmd->next != NULL && pipe(fd) == -1)
            return (free(pids), env);
        pids[i] = fork();
        if (pids[i] == -1)
            return (free(pids), NULL);
        else if (pids[i] == 0)
		{
            setup_child_process(input_fd, fd, cmd);
            env = execute_command(cmd, env);
            exit(0);
        }
		else
            setup_parent_process(&input_fd, fd);
        cmd = cmd->next;
        i++;
    }
    return (env);
}

char **handle_multiple_command(t_command **commande, char **env)
{
	pid_t *pids;
	int cmd_count;

	cmd_count = count_nbr_commands(*commande);
	pids = (pid_t *)malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (NULL);
	env = process_pipe(*commande, env, pids);
	wait_for_all_processes(pids, cmd_count);
	return (free(pids), env);
}
