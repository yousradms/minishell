/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:22:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/20 12:57:25 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	update_existing_env(t_env *env, char *arg, char *value)
{
	char	*new_value;

	if (ft_strchr(arg, '+') && ft_strchr(arg, '='))
	{
		new_value = ft_strjoin(env->value, value);
		free(env->value);
		env->value = new_value;
	}
	else if (ft_strchr(arg, '='))
	{
		free(env->value);
		env->value = ft_strdup(value);
	}
}

int	is_valid(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	check_arg(char *var)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(var[i]) || var[i] == '_'))
		return (0);
	while (var[i] && var[i] != '=' && var[i] != '+')
	{
		if (!is_valid(var[i]))
			return (0);
		i++;
	}
	if (var[i] && var[i] == '+' && (!var[i + 1] || var[i + 1] != '='))
		return (0);
	if (var[i] && var[i] != '+' && var[i] != '=')
		return (0);
	return (1);
}

char	*extract_var(char *line)
{
	int		i;
	int		key_len;
	char	*key;
	int		j;

	i = 0;
	key_len = 0;
	while (line[i] && line[i] != '=' && line[i] != '+')
	{
		key_len++;
		i++;
	}
	key = (char *)malloc(sizeof(char) * (key_len + 1));
	if (!key)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] && line[i] != '=' && line[i] != '+')
		key[j++] = line[i++];
	key[j] = '\0';
	return (key);
}

char	*extract_value(char *line)
{
	int		i;
	char	*value;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (!line[i])
		return (NULL);
	value = ft_strdup(line + i + 1);
	return (value);
}
