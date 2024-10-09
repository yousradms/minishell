/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:51:31 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 10:26:28 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL || array[0] == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->var);
		free(node->value);
		free(node);
	}
}

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void	remove_redirection_symbols(char **args, int index)
{
	int	j;

	free(args[index]);
	free(args[index + 1]);
	j = index;
	while (args[j] != NULL)
	{
		args[j] = args[j + 2];
		j++;
	}
	args[j] = NULL;
}

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->var);
		free(current->value);
		free(current);
		current = next;
	}
}
