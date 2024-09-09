/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/17 20:40:10 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	handle_redirect_in(t_command *cmd, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	cmd->in = fd;
	close(fd);
}

void	handle_redirect_out(t_command *cmd, char *filename, int append)
{
	int	flags;
	int	fd;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	cmd->out = fd;
	close(fd);
}

void	handle_redirections(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[i] != NULL)
	{
		if (ft_strcmp(cmd->arg[i], ">") == 0)
			handle_output_redirection(cmd, &i);
		else if (ft_strcmp(cmd->arg[i], ">>") == 0)
			handle_append_redirection(cmd, &i);
		else if (ft_strcmp(cmd->arg[i], "<" ) == 0)
			handle_input_redirection(cmd, &i);
		else if (ft_strcmp(cmd->arg[i], "<<") == 0)
			handle_heredoc_redirection(cmd, &i);
		i++;
	}
}
