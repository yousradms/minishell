/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:59:43 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/12 19:09:17 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	set_value(t_expansion_data *data, char **env)
{
	// printf("data expanded is:%s\n",*(data->expanded));
	char	*value;
	char	*new_expanded;

	value = get_env_value(*(data->var_name), env);
	if (value != NULL)
	{
		new_expanded = replace_variable(*(data->expanded), \
		value, *(data->i), *(data->j));
		free(*(data->expanded));
		*(data->expanded) = new_expanded;
		*(data->i) += ft_strlen(value);
		free(value);
	}
	else
	{
		// if(ft_strcmp(*(data->expanded),"$") == 0)
		// 	value = "$";
		new_expanded = replace_variable(*(data->expanded), \
		"", *(data->i), *(data->j));
		free(*(data->expanded));
		*(data->expanded) = new_expanded;
		*(data->i) += 1;
	}
}

char	*replace_variable(char *expanded, char *value, int i, int j)
{
	size_t	len_expanded;
	size_t	len_value;
	size_t	new_len;
	char	*new_expanded;

	len_expanded = ft_strlen(expanded);
	len_value = ft_strlen(value);
	new_len = len_expanded - (j - i) + len_value;
	new_expanded = malloc(new_len + 1);
	if (!new_expanded)
		return (NULL);
	ft_strncpy(new_expanded, expanded, i);
	ft_strcpy(new_expanded + i, value);
	ft_strcpy(new_expanded + i + len_value, expanded + j);
	return (new_expanded);
}

char	*get_env_value(char *var_name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, \
		ft_strlen(var_name)) == 0 && env[i][ft_strlen(var_name)] == '=')
			return (ft_strdup(env[i] + ft_strlen(var_name) + 1));
		i++;
	}
	return (NULL);
}

char	*extract_variable_name(char *expanded, int i, int j)
{
	int		var_length;
	char	*var_name;

	var_length = j - i - 1;
	var_name = malloc(var_length + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, expanded + i + 1, var_length);
	var_name[var_length] = '\0';
	return (var_name);
}

void	replace_numeric_variable(char **expanded, int *i, int j)
{
	char	*new_expanded;

	new_expanded = replace_variable(*expanded, "", *i, j + 1);
	if (!new_expanded)
		return ;
	free(*expanded);
	*expanded = new_expanded;
	*i += 1;
}
