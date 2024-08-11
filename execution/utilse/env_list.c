/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:11:16 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/11 18:49:40 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

static void	extract_var_value(char *envp_str, char **var, char **value)//yousra
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp_str, '=');
	if (equal_sign != NULL)
	{
		*var = (char *)malloc((equal_sign - envp_str + 1) * sizeof(char));
		*value = (char *)malloc((ft_strlen(equal_sign + 1) + 1) * sizeof(char));
		if (*var && *value)
		{
			ft_strncpy(*var, envp_str, equal_sign - envp_str);
			(*var)[equal_sign - envp_str] = '\0';
			ft_strcpy(*value, equal_sign + 1);
		}
	}
	else
	{
		*var = (char *)malloc((ft_strlen(envp_str) + 1) * sizeof(char));
		*value = NULL;
		if (*var)
			ft_strcpy(*var, envp_str);
	}
}

static int	process_envp_entry(char *envp_str, t_env **head, t_env **last)//yousra
{
	char	*var;
	char	*value;
	t_env	*new_env;

	var = NULL;
	value = NULL;
	extract_var_value(envp_str, &var, &value);
	if (!var || (ft_strchr(envp_str, '=') && !value))
	{
		free(var);
		free(value);
		return (-1);
	}
	new_env = create_env_node(var, value);
	if (!new_env)
	{
		free(var);
		free(value);
		return (-1);
	}
	append_env_node(head, last, new_env);
	return (0);
}

void	env_list(t_env **env, char **envp)//yousra
{
	t_env	*head;
	t_env	*last;
	int		i;

	if (!env || !envp)
		return ;
	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (process_envp_entry(envp[i], &head, &last) == -1)
			return ;
		i++;
	}
	*env = head;
}
