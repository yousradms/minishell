/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:17:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/25 16:14:56 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

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
