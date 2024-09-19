/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:18 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/19 17:42:30 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int	handle_herdoc(char *delimiter, char **env)
{
	int		temp_fd[2];
	int		flag;
	int		pid;
	char	*s;

	flag = determine_flag(delimiter);
	s = remove_quotes(delimiter);
	if (setup_temp_files(temp_fd) == -1)
		return (free(s), -1);
	rl_catch_signals = 1;
	signal(SIGINT, sigint_handler_herdoc);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		process_heredoc_input(temp_fd[0], s, flag, env);
	else
	{
		close(temp_fd[0]);
		waitpid(pid, 0, 0);
		rl_catch_signals = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigint_handler);
	}
	return (free(s), temp_fd[1]);
}

int	not_last(t_command *first, int i)
{
	i++;
	while (first->arg[i])
	{
		if (ft_strcmp(first->arg[i], "<<") == 0 && first->arg[i + 1])
			return (1);
		i++;
	}
	return (0);
}


void	handle_herddoce(t_command **command, char **env)
{
	t_command	*first;
	int			i;
	global = 0;
	first = *command;
	while (first != NULL )
	{
		i = 0;
		while (first->arg[i])
		{
			if (ft_strcmp(first->arg[i], "<<") == 0 && global == 0)
			{
				if (first->arg[i + 1])
				{
					first->my_fd = handle_herdoc(first->arg[i + 1], env);
					if (not_last(first, i))
						close(first->my_fd);
				}
			}
			i++;
		}
		first = first->next;
	}
}
