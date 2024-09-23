/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:15:41 by ydoumas           #+#    #+#             */
/*   Updated: 2024/09/20 16:18:36 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

char	*prepare_line(char **line)
{
	char	*new_line;
	char	*s;

	new_line = add_delimiter(*line);
	if (!new_line)
		return (NULL);
	s = ft_strtrim(new_line, " ");
	if (!s)
		return (NULL);
	free(new_line);
	return (s);
}

void	tokenize_line(t_node **head, char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		tokenize(result[i], head, get_state(result[i]));
		i++;
	}
}

void	free_resources(char **result, t_node *head, char *s)
{
	free(result);
	free_precedent_nodes(head);
	free(s);
}

int	is_ambiguous(t_node *head)
{
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == 3 || current->type == 4 || current->type == 5)
		{
			if (!current->next)
				return (0);
			current = current->next;
			while (current && current->type == 1)
				current = current->next;
			if (!current)
				return (0);
			if (current->type == 12)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
