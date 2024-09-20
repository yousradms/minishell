/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:21:42 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/20 12:56:04 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

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

static t_node	*move_to_previous_node(t_node *node)
{
	while (node && node->prev && node->prev->type == 1)
		node = node->prev;
	return (node);
}

static char	*add_quotes_to_content(char *content)
{
	char	*new_content;
	char	*temp_content;

	new_content = ft_strjoin("\"", content);
	if (!new_content)
		return (NULL);
	temp_content = new_content;
	new_content = ft_strjoin(temp_content, "\"");
	free(temp_content);
	return (new_content);
}

void	export_expand(t_node **head)
{
	t_node	*current;
	char	*new_content;

	current = *head;
	while (current != NULL)
	{
		if (current->content && \
		contain_env(current->content) && current->state == 1)
		{
			if (current->prev && current->prev->type == 9)
			{
				current = move_to_previous_node(current);
				if (current)
				{
					new_content = add_quotes_to_content(current->content);
					if (!new_content)
						return ;
					free(current->content);
					current->content = new_content;
				}
			}
		}
		current = current->next;
	}
}

void	add_limiter_type(t_node **head)
{
	t_node	*curr;

	curr = *head;
	while (curr)
	{
		if (curr->type == 6 && curr->next)
		{
			if (curr && curr->next)
				curr = curr->next;
			while (curr && curr->type == 1 && curr->next)
				curr = curr->next;
			if (curr && curr->type != 7)
				curr->type = 10;
		}
		curr = curr->next;
	}
}

static int	is_ambiguous(t_node *head)
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

static t_node	*tokenize_and_add_limiter(char **result)
{
	t_node	*head;

	head = NULL;
	tokenize_line(&head, result);
	add_limiter_type(&head);
	return (head);
}

static int	check_ambiguous_redirect(t_node *head)
{
	if (is_ambiguous(head))
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		exit_s(1, 1);
		return (1);
	}
	return (0);
}

static int	parse_and_expand(t_node **head, char **env)
{
	if (parsing(*head, env) == -1)
		return (-1);
	export_expand(head);
	expanding(*head, env);
	remove_dollor_quotes_delimiter(head);
	return (0);
}

char	**parsing_execute_command(char **line, char **env)
{
	char		**result;
	char		*s;
	t_node		*head;
	t_command	*commands;

	if (!check_quot(*line, '\'', '\"'))
		return (write(2, "unclosed quot\n", 14), env);
	s = prepare_line(line);
	if (!s)
		return (env);
	result = ft_split(s);
	if (!result)
		return (free(s), env);
	head = tokenize_and_add_limiter(result);
	if (parse_and_expand(&head, env) == -1)
		return (free_resources(result, head, s), env);
	if (check_ambiguous_redirect(head))
		return (free_resources(result, head, s), env);
	commands = ft_split2(&head);
	handle_herddoce(&commands, env);
	handle_quotes_ex(&commands);
	env = execute(&commands, env);
	return (free_commands(commands), free_resources(result, head, s), env);
}
