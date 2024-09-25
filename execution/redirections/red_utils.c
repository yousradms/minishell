/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:49:49 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/24 18:51:47 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	handle_output_redirection(t_command *cmd, int *index)
{
	handle_redirect_out(cmd, cmd->arg[*index + 1], 0);
	remove_redirection_symbols(cmd->arg, *index);
	(*index)--;//one command with multiple redirections go to begin and verify again
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
// Imaginons que l'index *index pointe initialement sur l'emplacement du symbole >> dans le tableau d'arguments (cmd->arg).
// Après avoir traité la redirection et supprimé les deux éléments (>> et le nom du fichier) avec remove_redirection_symbols, tous les éléments restants dans cmd->arg sont décalés d'une position vers la gauche.
// Si l'on ne décrémente pas *index, l'itération suivante sauterait un élément dans le tableau, car l'index augmenterait automatiquement dans la boucle après la suppression, ce qui fausserait le traitement des autres arguments.
// En décrémentant (*index), on compense la suppression des éléments pour permettre à la boucle qui parcourt les arguments de continuer correctement sans sauter d'éléments.


// Imaginons les arguments suivants avant le traitement :
// cmd->arg = {"echo", "hello", ">>", "file.txt", NULL}

// L'index *index pointe sur ">>".

// La redirection est traitée et les éléments ">>" et "file.txt" sont supprimés.

// cmd->arg devient :
// cmd->arg = {"echo", "hello", NULL}

// Si on ne faisait pas (*index)--, l'index passerait automatiquement à l'élément suivant, mais après suppression, on sauterait "hello".
// En faisant (*index)--, on ramène l'index au bon endroit pour ne pas sauter des arguments.