/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:18 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/29 08:34:18 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

static int del_without_quotes(char *s)
{
	if (s[0] != '\"' && s[0] != '\'')
		return (1);
	return (0);
}

static int setup_temp_files(int *temp_fd)
{
    unlink("temp.txt");
    temp_fd[0] = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    temp_fd[1] = open("temp.txt", O_RDONLY | O_TRUNC, 0644);
    if (temp_fd[0] == -1 || temp_fd[1] == -1)
        return (-1);
    unlink("temp.txt");
    return (0);
}

static void process_heredoc_input(int fd, char *s, int flag, char **env)
{
    char *line;
	char *str;

    while ((line = readline(">")))
    {
        if (ft_strncmp(line, s, ft_strlen(s)) == 0 && line[ft_strlen(s)] == '\0')
            break;
        if (flag && contain_env(line))
        {
            str = ft_strdup(line);
            set_expanded(&str, &line, env);
            free(str);
        }
        if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
        {
            free(line);
            free(s);
            close(fd);
            exit(1);
        }
        free(line);
    }
    free(line);
    exit(0);
}

//protection pid == -1
int handle_herdoc(char *delimiter, char **env)
{
	int temp_fd[2];
	int flag;
	int pid;
	char *s;

	if (del_without_quotes(delimiter))
    	flag = 1;
	else
    	flag = 0;
	s = remove_quotes(delimiter);
	if (setup_temp_files(temp_fd) == -1) 
        return (free(s), -1);
	signal(SIGINT, sigint_handler_herdoc);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 1;
	if ((pid = fork()) == 0)
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

void handle_herddoce(t_command **command, char **env)
{
	t_command *first;
	int i;

	first = *command;
	while (first != NULL)
	{
		i = 0;
		while (first->arg[i])
		{
			if (ft_strcmp(first->arg[i], "<<") == 0)
			{
				if (first->arg[i + 1])
					first->my_fd = handle_herdoc(first->arg[i + 1],env);  
			}
			i++;
		}
		first = first->next;
	}  
}
