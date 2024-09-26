/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:07:08 by ydoumas           #+#    #+#             */
/*   Updated: 2024/09/26 12:07:05 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	determine_flag(char *delimiter)
{
	if (del_without_quotes(delimiter))
		return (1);
	else
		return (0);
}

static t_node	*move_to_previous_node(t_node *node)
{
	while (node && node->prev && node->prev->type == 1)
		node = node->prev;
	return (node);
}

static char	*add_quotes_to_content(char *content)
{
	char	*new_content;
	char	*temp_content;

	new_content = ft_strjoin("\"", content);
	if (!new_content)
		return (NULL);
	temp_content = new_content;
	new_content = ft_strjoin(temp_content, "\"");
	free(temp_content);
	return (new_content);
}

void	export_expand(t_node **head)
{
	t_node	*current;
	char	*new_content;

	current = *head;
	while (current != NULL)
	{
		if (current->content && \
		contain_env(current->content) && current->state == 1)
		{
			if (current->prev && current->prev->type == 9)
			{
				current = move_to_previous_node(current);
				if (current)
				{
					new_content = add_quotes_to_content(current->content);
					if (!new_content)
						return ;
					free(current->content);
					current->content = new_content;
				}
			}
		}
		current = current->next;
	}
}

void	add_limiter_type(t_node **head)
{
	t_node	*curr;

	curr = *head;
	while (curr)
	{
		if (curr->type == 6 && curr->next)
		{
			if (curr && curr->next)
				curr = curr->next;
			while (curr && curr->type == 1 && curr->next)
				curr = curr->next;
			if (curr && curr->type != 7)
				curr->type = 10;
		}
		curr = curr->next;
	}
}
