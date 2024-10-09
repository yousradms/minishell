/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 12:03:10 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_dollor_quotes(t_node **list)
{
	t_node	*current;

	if (!list || !*list)
		return ;
	current = *list;
	while (current != NULL && current->next != NULL)
	{
		if (current->type == 7 && current->state == 1 \
		&& current->next && current->next->content[0] \
		&& (current->next->content[0] == '\"' \
		|| current->next->content[0] == '\''))
			current->content = ft_strdup("");
		current = current->next;
	}
}

static void	process_node(t_node *current)
{
	int		i;
	char	*temp;

	i = 0;
	while (current->content[i])
	{
		if (current->content[i] && current->content[i + 1] \
		&& current->content[i] == '$' && \
		(i == 0 || (current->content[i - 1] != '\"' \
		&& current->content[i - 1] != '\'')) && \
		(current->content[i + 1] == '\"' || current->content[i + 1] == '\''))
		{
			temp = ft_strjoin(ft_substr(current->content, 0, i), \
			ft_strdup(current->content + i + 1));
			if (!temp)
				return ;
			free(current->content);
			current->content = temp;
		}
		i++;
	}
}

void	remove_dollor_quotes_delimiter(t_node **list)
{
	t_node	*current;

	if (!list || !*list)
		return ;
	current = *list;
	while (current != NULL)
	{
		if (current->type == 10)
			process_node(current);
		current = current->next;
	}
}

static int	empty_contain_space(t_node *current, char **env)
{
	char	*str;
	char	*content;

	content = ft_strdup(current->content);
	str = ft_strdup(current->content);
	set_expanded(&str, &content, env);
	if (ft_strcmp(content, "") == 0 || ft_strchr(content, ' ') != NULL)
	{
		free(content);
		free(str);
		return (1);
	}
	return (free(content), free(str), 0);
}

int	symbol_redirect_bef(t_node *current, char **env)
{
	t_node	*curr;

	curr = current;
	if (curr->prev)
		curr = curr->prev;
	else
		return (0);
	while (curr && curr->type == 1)
		curr = curr->prev;
	if (curr && (curr->type == REDIN \
	|| curr->type == REDOUT || curr->type == APPEND))
		return (empty_contain_space(current, env));
	return (0);
}
