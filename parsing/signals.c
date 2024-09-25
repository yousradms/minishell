/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:58 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/25 18:00:24 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	sigint_handler(int signo)
{
	int	i;

	if (signo == SIGINT)
	{
		i = wait(NULL);
		if (i <= 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			exit_s(1, 1);
		}
		else
		{
			printf("\n");
			exit_s(128 + signo, 1);
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

	if (WIFEXITED(status))
	{
		exit_s(WEXITSTATUS(status), 1);
	}
	else if (WIFSIGNALED(status))
	{
		signal_number = WTERMSIG(status);
		exit_s(128 + signal_number, 1);
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
