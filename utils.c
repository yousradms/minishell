/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:15:41 by ydoumas           #+#    #+#             */
/*   Updated: 2024/09/26 12:09:40 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
