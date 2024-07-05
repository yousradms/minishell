/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:53:54 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/04 20:35:48 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(t_command **command, t_env **envp)
{
	(void)command; // Suppress unused parameter warning
	t_env *env; // Dereference envp to get the linked list head
	
	env = *envp;
	if (env == NULL)
		return;
	// Iterate through the linked list of environment variables
	while (env != NULL)
	{
		printf("%s=%s\n", env->var, env->value);
		env = env->next; // Move to the next node
	}
}
