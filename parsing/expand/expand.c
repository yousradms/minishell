/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/20 18:22:33 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	handle_heredoc_expand(t_node **current, int *in_herdoc)
{
	if ((*current)->type == 6)
	{
		*in_herdoc = 1;
		while ((*current)->next && (*current)->next->type == 1)
			*current = (*current)->next;
	}
}

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

t_node	*process_current_node(t_node *current, char **env, int *in_herdoc)
{
	while (current && current->type == 1)
		current = current->next;
	if (current == NULL)
		return (NULL);
	if (*in_herdoc && current->next)
		current = current->next;
	if (current->type == 9 && contain_env(current->content) && *in_herdoc != 1)
		expand_variable(current, env);
	else if (current->type == 9 && contain_home_after_quote(current->content) \
		&& *in_herdoc != 1 && (current->next == NULL \
		|| current->next->type == 1))
		expand_home_directory(current);
	else if (current->type == 9 && \
	contain_home1(current->content) && !(*in_herdoc))
		expand_home_directory(current);
	return (current);
}
