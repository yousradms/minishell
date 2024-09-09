/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:18 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:51:14 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int	handle_herdoc(char *delimiter, char **env)//yousra
{
	int		temp_fd[2];
	int		flag;
	int		pid;
	char	*s;

	flag = determine_flag(delimiter);
	s = remove_quotes(delimiter);
	if (setup_temp_files(temp_fd) == -1)
		return (free(s), -1);
	signal(SIGINT, sigint_handler_herdoc);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 1;
	pid = fork();
	if (pid == 0)
		process_heredoc_input(temp_fd[0], s, flag, env);
	else
	{
		waitpid(pid, 0, 0);
		rl_catch_signals = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigint_handler);
	}
	return (free(s), temp_fd[1]);
}

void	handle_herddoce(t_command **command, char **env)//yousra
{
	t_command	*first;
	int			i;

	first = *command;
	while (first != NULL)
	{
		i = 0;
		while (first->arg[i])
		{
			if (ft_strcmp(first->arg[i], "<<") == 0)
			{
				if (first->arg[i + 1])
					first->my_fd = handle_herdoc(first->arg[i + 1], env);
			}
			i++;
		}
		first = first->next;
	}
}
