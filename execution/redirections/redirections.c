/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 09:22:24 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_redirect_in(t_command *cmd, char *filename)
{
	int	fd;

	if (filename[0] == '$')
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		// exit_s(1, 1);
		cmd->in = -1;
		// return ;
		exit(1);
	}
	// printf("go there\n");
	fd = open(filename, O_RDONLY);
	// printf("enter here with filename==>>%s",filename);
	if (fd == -1)
	{
		ft_putstr_fd("NO such file or directory\n", 2);
		// free(filename);
		// exit_s(1, 1);
		cmd->in = -1;
		// return ;
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Minishell :dup2");
		close(fd);
		// return ;
		exit(1);
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
	if (filename[0] == '$')
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		exit(1);
	}
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
