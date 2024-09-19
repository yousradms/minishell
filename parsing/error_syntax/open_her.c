/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_her.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:00:30 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/19 17:44:16 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	open_here(t_node *token, t_node *ptr_err, char **env)
{
	int	fd;

	while (token && token != ptr_err)
	{
		if (token->type == 6)
		{
			token = token->next;
			while (token && token != ptr_err && token->type == 1)
				token = token->next;
			if (token && token != ptr_err)
			{
				fd = handle_herdoc(token->content, env);
				close(fd);
			}
		}
		token = token->next;
	}
}
