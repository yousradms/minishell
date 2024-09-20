/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:16:04 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/20 15:38:11 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int	del_without_quotes(char *s)
{
	if (ft_strchr(s,'\"') == NULL && ft_strchr(s,'\'') == NULL)
		return (1);
	return (0);
}

void init_data(int *i, char **file_name, char **str)
{
	*i = 0;
	*file_name = ft_strdup("/tmp/");
	*str = NULL;
}

char	*create_heredoc_file()
{
	int		fd;
	char	*file_name;
	char	*str;
	int		i;
	char	fm[2];

	init_data(&i, &file_name, &str);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (free(file_name), NULL);
	while (i < 20)
	{
		read(fd, fm, 1);
		fm[1] = '\0';
		if (!ft_isalpha(fm[0]))
			continue ;
		str = file_name;
		file_name = ft_strjoin(str, fm);
		free(str);
		i++;
	}
	return (close(fd), file_name);
}

int	setup_temp_files(int *temp_fd)
{
	char *file_name;

	file_name = create_heredoc_file();
	temp_fd[0] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	temp_fd[1] = open(file_name, O_RDONLY | O_TRUNC, 0644);
	free(file_name);
	if (temp_fd[0] == -1 || temp_fd[1] == -1)
		return (-1);
	return (0);
}

int	is_end_of_heredoc(char *line, char *s)
{
	if (!line)
		return (1);
	return (ft_strncmp(line, s, ft_strlen(s)) == 0 \
	&& line[ft_strlen(s)] == '\0');
}

static void	expand_environment_variables(char **line, char **str, char **env)
{
	if (contain_env(*line))
	{
		*str = ft_strdup(*line);
		set_expanded(str, line, env);
		free(*str);
	}
}

void	process_heredoc_input(int fd, char *s, int flag, char **env)
{
	char	*line;
	char	*str;

	while (1)
	{
		line = readline(">");
		if (is_end_of_heredoc(line, s))
		{
			close(fd);
			break ;
		}
		if (flag)
			expand_environment_variables(&line, &str, env);
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
		{
			free(line);
			free(s);
			close(fd);
			exit(1);
		}
		free(line);
	}
	close(fd);
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
