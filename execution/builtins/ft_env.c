/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:53:54 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:47:03 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	ft_env(t_env **envp)//yousra
{
	t_env	*env;

	env = *envp;
	if (env == NULL)
		return ;
	while (env != NULL)
	{
		if (env->var && env->value != NULL)
			printf("%s=%s\n", env->var, env->value);
		env = env->next;
	}
}
