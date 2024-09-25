/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/25 16:00:33 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

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
	struct termios	termios_p;//une structure qui contient des paramètres de configuration pour le terminal, utilisée ici pour sauvegarder l'état du terminal

	tcgetattr(0, &termios_p);//Cette fonction récupère les paramètres 
	//actuels du terminal associé à l'entrée standard (0 pour STDIN_FILENO) 
	//et les stocke dans termios_p
	while (1)
	{
		line = read_input();
		if (line[0] == '\0' || just_spaces(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		//varaibles utilisees pour stocker les copies des descripteurs de fichiers
		//d'entree et de sortie standard
		//ceci permet de restaurer l'etat initial apres l'execution d'une commande
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		if (stdin_backup == -1 || stdout_backup == -1)
			perror("dup");
		envp = parsing_execute_command(&line, envp);
		restore_io(stdin_backup, stdout_backup);
		free(line);
		tcsetattr(0, 0, &termios_p);//Après chaque exécution de commande, les paramètres du terminal sont restaurés à l'état précédemment sauvegardé avec tcsetattr
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
