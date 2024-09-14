/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:16:04 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/12 18:47:39 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int	del_without_quotes(char *s)
{
	if (s[0] != '\"' && s[0] != '\'')
		return (1);
	return (0);
}

int	setup_temp_files(int *temp_fd)
{
	unlink("temp.txt");
	temp_fd[0] = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	temp_fd[1] = open("temp.txt", O_RDONLY | O_TRUNC, 0644);
	if (temp_fd[0] == -1 || temp_fd[1] == -1)
		return (-1);
	unlink("temp.txt");
	return (0);
}

int	is_end_of_heredoc(char *line, char *s)
{
	return (ft_strncmp(line, s, ft_strlen(s)) == 0 \
	&& line[ft_strlen(s)] == '\0');
}

void	process_heredoc_input(int fd, char *s, int flag, char **env)
{
	char	*line;
	char	*str;

	while (1)
	{
		line = readline(">");
		if (is_end_of_heredoc(line, s))
			break ;
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

int	determine_flag(char *delimiter)
{
	if (del_without_quotes(delimiter))
		return (1);
	else
		return (0);
}
