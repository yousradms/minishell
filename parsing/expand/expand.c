/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/25 15:48:39 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

static void	handle_heredoc_expand(t_node **current, int *in_herdoc)
{
	if ((*current)->type == 6)
	{
		*in_herdoc = 1;
		while ((*current)->next && (*current)->next->type == 1)
			*current = (*current)->next;
	}
}

static void	remove_dollor_quotes(t_node **list)
{
	t_node	*current;

	if (!list || !*list)
		return ;
	current = *list;
	while (current != NULL && current->next != NULL)
	{
		if (ft_strcmp(current->content, "$") == 0 \
		&& current->next && current->next->content[0] \
		&& (current->next->content[0] == '\"' \
		|| current->next->content[0] == '\'') && current->state == GENERAL \
		&& (current->next->state == DQ || current->next->state == SQ))
			current->content = ft_strdup("");
		else
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

void	set_expanded(char **str, char **content, char **env)
{
	char	*expanded;
	int		i;
	int		j;

	if (!str || !*str || !content || !env)
		return ;
	expanded = ft_strdup(*str);
	if (!expanded)
		return ;
	i = 0;
	while (expanded[i])
	{
		if (expanded[i] == '$')
		{
			j = i + 1;
			handle_special_cases(&expanded, &i, &j, env);
			if (ft_strchr(expanded, '$') == NULL \
			|| ft_strcmp(expanded, "") == 0)
				break ;
		}
		else
			i++;
	}
	free(*content);
	*content = expanded;
}

void	expanding(t_node *list, char **env)
{
	t_node	*current;
	int		in_herdoc;

	if (!list)
		return ;
	remove_dollor_quotes(&list);
	in_herdoc = 0;
	current = list;
	while (current != NULL)
	{
		handle_heredoc_expand(&current, &in_herdoc);
		if (current == NULL)
			break ;
		current = process_current_node(current, env, &in_herdoc);
		if (current != NULL)
			current = current->next;
		in_herdoc = 0;
	}
}
