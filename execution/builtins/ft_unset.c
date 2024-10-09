/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:03:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 09:19:08 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_env_node(t_env **envp, char *var_name)
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

void	ft_unset(char *var_names[], int num_vars, t_env **envp)
{
	int	i;
	int	status;
	char	*ex;

	i = 0;
	status = 0;
	while (i < num_vars)
	{
		if (!check_arg(var_names[i]))
		{
			write(2, "Minishell: `", 12);
			write(2, var_names[i], ft_strlen(var_names[i]));
			write(2, "': not a valid identifier\n", 27);
			status = 1;
		}
		else
			remove_env_node(envp, var_names[i]);
		i++;
	}
	ex = exit_s(status, 1);
	free(ex);
}
