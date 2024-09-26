/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:08:50 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	rl_catch_signals = 0;
}

char	*read_input(void)
{
	char	*line;

	line = readline("minishell🥶😁");
	if (!line)
	{
		write(2, "exit\n", 6);
		exit(ft_atoi(exit_s(0, 0)));
	}
	return (line);
}

void	restore_io(int stdin_backup, int stdout_backup)
{
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1 || \
	dup2(stdin_backup, STDIN_FILENO) == -1)
		perror("dup2");
	close(stdin_backup);
	close(stdout_backup);
	while (wait(NULL) != -1)
		;
}

void	run_shell_loop(char **envp)
{
	char			*line;
	int				stdin_backup;
	int				stdout_backup;
	struct termios	termios_p;

	tcgetattr(0, &termios_p);
	while (1)
	{
		line = read_input();
		if (line[0] == '\0' || just_spaces(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		if (stdin_backup == -1 || stdout_backup == -1)
			perror("dup");
		envp = parsing_execute_command(&line, envp);
		restore_io(stdin_backup, stdout_backup);
		free(line);
		tcsetattr(0, 0, &termios_p);
	}
}

int	main(int ac, char **av, char **env)
{
	char	**envp;

	(void)ac;
	(void)av;
	setup_signals();
	envp = set_env(env);
	run_shell_loop(envp);
	return (0);
}
