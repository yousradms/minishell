/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 12:06:12 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_redirect_in(t_command *cmd, char *filename)
{
	int	fd;

	if (filename[0] == '$')
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		cmd->in = -1;
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("NO such file or directory\n", 2);
		cmd->in = -1;
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Minishell :dup2");
		close(fd);
		exit(1);
	}
	cmd->in = fd;
	close(fd);
}

static int	determine_flags(int append)
{
	if (append)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (O_WRONLY | O_CREAT | O_TRUNC);
}

void	handle_redirect_out(t_command *cmd, char *filename, int append)
{
	int	flags;
	int	fd;

	if (filename[0] == '$')
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		exit(1);
	}
	flags = determine_flags(append);
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("NO such file or directory\n", 2);
		cmd->out = -1;
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(1);
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
		if (cmd->in == -1 || cmd->out == -1)
			return ;
		i++;
	}
}
