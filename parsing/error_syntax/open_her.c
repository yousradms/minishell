/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_her.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:00:30 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 09:27:16 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void open_here(t_node *token, t_node *ptr_err)
{
    while (token && token != ptr_err)
	{
		if (token->type == 6)//<<
        {
            token = token->next;
            while (token && token != ptr_err && token->type == 1)
                token = token->next;
            if (token && token != ptr_err)
            {
                handle_herdoc(token->content, 0);
            }
        }
        token = token->next;
	}
}