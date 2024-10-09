/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:53:54 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 11:05:56 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env **envp)
{
	t_env	*env;
	char	*ex;

	env = *envp;
	while (env != NULL)
	{
		// printf("[%s]\n", env->value);
		// exit(0);
		if (env->var && env->value != NULL)
			printf("%s=%s\n", env->var, env->value);
		env = env->next;
	}
	ex = exit_s(0, 1);
	free(ex);
}
