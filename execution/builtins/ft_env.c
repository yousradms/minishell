/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:53:54 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 12:07:11 by ydoumas          ###   ########.fr       */
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
		if (env->var && env->value != NULL)
			printf("%s=%s\n", env->var, env->value);
		env = env->next;
	}
	ex = exit_s(0, 1);
	free(ex);
}
