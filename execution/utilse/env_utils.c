/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:58:11 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:50:02 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

t_env	*create_env_node(char *var, char *value)//yousra
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (new_env)
	{
		new_env->var = var;
		new_env->value = value;
		new_env->next = NULL;
		new_env->prev = NULL;
	}
	return (new_env);
}

void	append_env_node(t_env **head, t_env **last, t_env *new_env)//yousra
{
	if (*head == NULL)
		*head = new_env;
	else
	{
		(*last)->next = new_env;
		new_env->prev = *last;
	}
	*last = new_env;
}

void	add_new_env(t_env **envp, char *key, char *value)//yousra
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->var = ft_strdup(key);
	if (value)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	new_env->next = *envp;
	*envp = new_env;
}
