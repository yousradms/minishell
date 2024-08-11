/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:21:42 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/10 17:31:32 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prepare_line(char **line)
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

static void	tokenize_line(t_node **head, char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		tokenize(result[i], head, get_state(result[i]));
		i++;
	}
}

static void	free_resources(char **result, t_node *head, char *s)
{
	free(result);
	free_precedent_nodes(head);
	free(s);
}

void	export_expand(t_node **head)
{
	t_node	*current;

	current = *head;
	while (current != NULL)
	{
		if (current->content && \
		contain_env(current->content) && current->state == 1)
		{
			if (current->prev && current->prev->type == 9)
			{
				while (current && current->prev && current->prev->type == 1)
					current = current->prev;
				if (current)
				{
					current->content = ft_strjoin("\"", current->content);
					current->content = ft_strjoin(current->content, "\"");
				}
			}
		}
		current = current->next;
	}
}

char	**parsing_execute_command(char **line, char **env)
{
	char		**result;
	char		*s;
	t_node		*head;
	t_command	*commands;

	if (!check_quot(*line, '\'', '\"'))
		return (write(2, "UNCLOSED QUOT\n", 14), env);
	s = prepare_line(line);
	if (!s)
		return (env);
	result = ft_split(s);
	if (!result)
		return (free(s), env);
	head = NULL;
	tokenize_line(&head, result);
	if (parsing(head, env) == -1)
		return (free_resources(result, head, s), env);
	export_expand(&head);
	expanding(head, env);
	commands = ft_split2(&head);
	handle_herddoce(&commands, env);
	handle_quotes_ex(&commands);
	env = execute(&commands, env);
	return (free_commands(commands), free_resources(result, head, s), env);
}
