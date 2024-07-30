/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/28 20:31:34 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

char *get_env_value(char *var_name, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0 && env[i][ft_strlen(var_name)] == '=')
			return ft_strdup(env[i] + ft_strlen(var_name) + 1);
		i++;
	}
	return (NULL);
}

char *replace_variable( char *expanded,  char *value, int i, int j)
{
	size_t len_expanded;
	size_t len_value;
	size_t new_len;
	char *new_expanded;
	
	len_expanded = ft_strlen(expanded);
	len_value = ft_strlen(value);
	new_len = len_expanded - (j - i) + len_value;
	new_expanded = malloc(new_len + 1);
	if (!new_expanded)
		return (NULL);
	ft_strncpy(new_expanded, expanded, i);
	ft_strcpy(new_expanded + i, value);
	ft_strcpy(new_expanded + i + len_value, expanded + j);
	return (new_expanded);
}

void set_value(int *i, int *j, char **var_name, char **expanded, char **env)
{
	char *value;
	char *new_expanded;

	value = get_env_value(*var_name, env);
	if (value != NULL)
	{
		new_expanded = replace_variable(*expanded, value, *i, *j);
		free(*expanded);
		*expanded = new_expanded;
		*i += ft_strlen(value);
		free(value);
	}
	else
	{
		new_expanded = replace_variable(*expanded, "", *i, *j);
		free(*expanded);
		*expanded = new_expanded;
		*i += 1;
	}
}

static void handle_heredoc_expand(t_node **current, int *in_herdoc)
{
	if ((*current)->type == 6)
	{
		*in_herdoc = 1;
		while ((*current)->next && (*current)->next->type == 1)
			*current = (*current)->next;
	}
}

void expanding(t_node *list, char **env)
{
	t_node *current;
	int in_herdoc;
	
	if (!list)
		return;
	in_herdoc = 0;
	current = list;
	while (current != NULL)
	{
		handle_heredoc_expand(&current, &in_herdoc);
		if (current == NULL)
			break;
		while(current && current->type == 1)
			current = current->next;
		if (current == NULL)
			break;
		if (in_herdoc && current->next)
			current = current->next;
		if (current->type == 9 && contain_env(current->content) && in_herdoc != 1)
			expand_variable(current, env);
		else if (current->type == 9 && contain_home_after_quote(current->content) && in_herdoc != 1)
			expand_home_directory(current);
		current = current->next;
		in_herdoc = 0;
	}
}
