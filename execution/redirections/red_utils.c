/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:49:49 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:05:48 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_output_redirection(t_command *cmd, int *index)
{
	handle_redirect_out(cmd, cmd->arg[*index + 1], 0);
	remove_redirection_symbols(cmd->arg, *index);
	(*index)--;
}

void	handle_append_redirection(t_command *cmd, int *index)
{
	handle_redirect_out(cmd, cmd->arg[*index + 1], 1);
	remove_redirection_symbols(cmd->arg, *index);
	(*index)--;
}

void	handle_input_redirection(t_command *cmd, int *index)
{
	handle_redirect_in(cmd, cmd->arg[*index + 1]);
	remove_redirection_symbols(cmd->arg, *index);
	(*index)--;
}

void	handle_heredoc_redirection(t_command *cmd, int *index)
{
	dup2(cmd->my_fd, STDIN_FILENO);
	close(cmd->my_fd);
	remove_redirection_symbols(cmd->arg, *index);
	(*index)--;
}
