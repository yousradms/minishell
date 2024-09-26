/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:21:42 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:09:36 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*tokenize_and_add_limiter(char **result)
{
	t_node	*head;

	head = NULL;
	tokenize_line(&head, result);
	add_limiter_type(&head);
	return (head);
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
	commands = ft_split2(&head);
	handle_herddoce(&commands, env);
	handle_quotes_ex(&commands);
	env = execute(&commands, env);
	return (free_commands(commands), free_resources(result, head, s), env);
}
