/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:49 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/10 17:07:52 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	tokenize(char *s, t_node **head, t_state state)
{
	if (ft_strcmp(s, " ") == 0)
		add_node(head, create_node(s, WSPACE, state));
	else if (ft_strcmp(s, "|") == 0)
		add_node(head, create_node(s, PIPE, state));
	else if (ft_strcmp(s, "<") == 0)
		add_node(head, create_node(s, REDIN, state));
	else if (ft_strcmp(s, ">") == 0)
		add_node(head, create_node(s, REDOUT, state));
	else if (ft_strcmp(s, ">>") == 0)
		add_node(head, create_node(s, APPEND, state));
	else if (ft_strcmp(s, "<<") == 0)
		add_node(head, create_node(s, HEREDOC, state));
	else if (ft_strcmp(s, "$") == 0)
		add_node(head, create_node(s, SIGN, state));
	else if (s && *s)
		add_node(head, create_node(s, WORD, state));
}
