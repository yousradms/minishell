/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:58 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/10 20:12:29 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int signo)
{
	int		i;
	char	*ex;

	i = wait(NULL);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (i <= 0)
		ex = exit_s(1, 1);
	else
		ex = exit_s(128 + signo, 1);
	free(ex);
}

void	handle_sigquit(void)
{
	if (waitpid(-1, 0, WNOHANG) == 0)
		printf("Quit: 3\n");
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
		handle_sigint(signo);
	else if (signo == SIGQUIT)
		handle_sigquit();
}

void	handle_exit_status(int status)
{
	int		signal_number;
	char	*ex;

	if (WIFEXITED(status) && g_global != SIGINT)
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
			g_global = SIGINT;
			exit_s(1, 1);
			return ;
		}
		else
			exit(1);
	}
}
