/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/22 14:31:05 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *create_node(char *content, int type,int state)
{
    t_node *node = malloc(sizeof(t_node));
    node->content = content;
    node->type = type;
    node->state = state;
    node->next = NULL;
    return (node);
}

void add_node(t_node **head, t_node *node)
{
    if (*head == NULL)
        *head = node;
    else
    {
        t_node *current = *head;
        while (current->next!= NULL)
            current = current->next;
        current->next = node; 
    }
}

void print_list(t_node *head)
{
    t_node *temp = head;
    
    while(temp != NULL)
    {
        printf("content is :[%s]     ",temp->content);
        printf("type is :[%d]    ",temp->type);
        printf("state is :[%d]   \n",temp->state);
        temp = temp->next;
    }
}

void print_list2(t_command *command)
{
    t_command *first = command;
    while (first != NULL) {
        int i = 0;
        while (first->arg[i]) {
            printf("%s  ", first->arg[i]);
            i++;
        }
        printf("\n");
        first = first->next;
    }
}

void free_precedent_nodes(t_node *head)
{
    t_node *current = head;
    while (current!= NULL)
    {
        t_node *next = current->next;
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

int count_elem_command(t_command *command)
{
    t_command *first;
    int count;
    
    first = command;
    count = 0;
    while(first != NULL)
    {
        count++;
        first = first->next;
    }
    return(count);
}
