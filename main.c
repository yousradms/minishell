/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:54:22 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	setup_signals(void)//yousra
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
		printf("exit\n");
		exit(ft_atoi(exit_s(0, 0)));
	}
	return (line);
}

int	main(int ac, char **av, char **env)
{
	char	**envp;
	char	*line;

	(void)ac;
	(void)av;
	setup_signals();
	envp = set_env(env);
	while (1)
	{
		line = read_input();
		if (line[0] == '\0' || just_spaces(line))
		{
			free(line);
			continue ;
		}
		if (strlen(line) > 0)
		{
			add_history(line);
			envp = parsing_execute_command(&line, envp);
		}
		free(line);
	}
	return (0);
}
