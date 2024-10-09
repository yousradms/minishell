/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:17:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 12:04:19 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_home_directory(t_node *current)
{
	char	*new_content;
	char	*home;

	if (!current || !current->content)
		return ;
	new_content = NULL;
	home = getenv("HOME");
	if (!home)
		return ;
	if (current->content[0] == '~')
	{
		if (current->content[1] == '\0')
			new_content = ft_strdup(home);
		else if (current->content[1] == '/')
			new_content = ft_strjoin(home, current->content + 1);
	}
	if (new_content)
	{
		free(current->content);
		current->content = new_content;
	}
}

int	contain_home1(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] && s[i] == '~' && s[i + 1] && s[i + 1] == '/')
		return (1);
	return (0);
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

	if (!list)
		return ;
	remove_dollor_quotes(&list);
	current = list;
	while (current != NULL)
	{
		current = process_current_node(current, env);
		if (current != NULL)
			current = current->next;
	}
}

t_node	*process_current_node(t_node *current, char **env)
{
	if (current->type == 9 && contain_env(current->content) \
	&& !symbol_redirect_bef(current, env))
		expand_variable(current, env);
	else if (current->type == 9 && \
	contain_home_after_quote(current->content) && \
	(current->next == NULL || current->next->type == 1))
		expand_home_directory(current);
	else if (current->type == 9 && \
	contain_home1(current->content))
		expand_home_directory(current);
	return (current);
}
