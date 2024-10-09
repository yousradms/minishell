/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:58 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 09:23:46 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signo)
{
	int	i;
	char	*ex;

	if (signo == SIGINT)
	{
		i = wait(NULL);
		if (i <= 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			ex = exit_s(1, 1);
			free(ex);
		}
		else
		{
			printf("\n");
			ex = exit_s(128 + signo, 1);
			free(ex);
		}
	}
	else if (signo == SIGQUIT)
	{
		if (waitpid(-1, 0, WNOHANG) == 0)
			printf("Quit: 3\n");
	}
}

void	handle_exit_status(int status)
{
	int	signal_number;
	char	*ex;

	if (WIFEXITED(status))
	{
		ex = exit_s(WEXITSTATUS(status), 1);
		free(ex);
	}
	else if (WIFSIGNALED(status))
	{
		signal_number = WTERMSIG(status);
		ex = exit_s(128 + signal_number, 1);
		free(ex);
	}
}

void	sigint_handler_herdoc(int signo)
{
	if (signo == SIGINT)
	{
		if (waitpid(-1, 0, WNOHANG) == 0)
		{
			printf("\n");
			g_global = 1;
			return ;
		}
		else
			exit(1);
	}
}
