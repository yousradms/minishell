/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:03:10 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 11:32:00 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_var_str(char *var, char *value)
{
	int		var_len;
	int		value_len;
	char	*env_var_str;

	if (var)
		var_len = ft_strlen(var);
	else
		var_len = 0;
	if (value && value[0])
		value_len = ft_strlen(value);
	else
		value_len = 0;
	env_var_str = (char *)malloc((var_len + value_len + 2) * sizeof(char));
	if (!env_var_str)
		return (NULL);
	ft_strcpy(env_var_str, var);
	// printf("env p_str : %s\n", env_var_str);
	// printf("value : %s\n",value);
	if (value)
	{
		ft_strcat(env_var_str, "=");
		ft_strcat(env_var_str, value);
	}
	return (env_var_str);
}

static void	copy_env_vars(t_env *env, char **envp)
{
	t_env	*current;
	int		i;

	current = env;
	i = 0;
	while (current != NULL)
	{
		envp[i] = create_env_var_str(current->var, current->value);
		if (!envp[i])
			return ;
		i++;
		current = current->next;
	}
	envp[i] = NULL;
}

char	**env_to_char_array(t_env *env)
{
	int		count;
	char	**envp;

	count = count_env_vars(env);
	envp = (char **)malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	copy_env_vars(env, envp);
	return (envp);
}
