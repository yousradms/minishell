/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/10 17:23:57 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

t_node	*create_node(char *content, int type, int state)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->state = state;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_node(t_node **head, t_node *node)
{
	t_node	*current;

	if (*head == NULL)
	{
		*head = node;
		node->prev = NULL;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
		node->prev = current;
	}
}

void	free_precedent_nodes(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

t_node	*ft_lstlast(t_node *lst)
{
	t_node	*temp;

	if (lst == NULL)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
