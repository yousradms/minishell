/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:06:55 by ksellami         ###   ########.fr       */
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

t_node	*process_current_node(t_node *current, char **env)
{
	if (current->type == 9 && contain_env(current->content))
		expand_variable(current, env);
	else if (current->type == 9 && contain_home_after_quote(current->content) \
		 && (current->next == NULL \
		|| current->next->type == 1))
		expand_home_directory(current);
	else if (current->type == 9 && \
	contain_home1(current->content))
		expand_home_directory(current);
	return (current);
}
