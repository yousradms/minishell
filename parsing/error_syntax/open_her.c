/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_her.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:00:30 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:06:24 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
