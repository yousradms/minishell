/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:03:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:47:24 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

static void	remove_env_node(t_env **envp, char *var_name)//yousra
{
	t_env	*current;
	t_env	*prev;

	current = *envp;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, var_name) == 0)
		{
			if (prev == NULL)
				*envp = current->next;
			else
				prev->next = current->next;
			free_env_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(char *var_names[], int num_vars, t_env **envp)//yousra
{
	int	i;

	i = 0;
	while (i < num_vars)
	{
		remove_env_node(envp, var_names[i]);
		i++;
	}
}
