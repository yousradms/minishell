/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:09:19 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/05 20:48:09 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_variable(char **expanded, int *i, int *j, char **env)
{
	int					k;
	char				*var_name;
	t_expansion_data	data;

	k = *j;
	while ((*expanded)[k] != '\0' && (*expanded)[k] != ' ' \
	&& (*expanded)[k] != '$' && is_valid_char((*expanded)[k]))
		k++;
	*j = k;
	var_name = extract_variable_name(*expanded, *i, *j);
	if (var_name == NULL || ft_strlen(var_name) == 0)
	{
		*i += 1;
		free(var_name);
		return ;
	}
	data.i = i;
	data.j = j;
	data.var_name = &var_name;
	data.expanded = expanded;
	set_value(&data, env);
	free(var_name);
}

int	validate_inputs(char **expanded, int *i, int *j, char **env)
{
	return (expanded && *expanded && i && j && env);
}

char	*exit_s(int new_one, int set)
{
	static int	x;

	if (set == 1)
		x = new_one;
	else
		return (ft_itoa(x));
	return (NULL);
}

void	replace_special_variable(char **expanded, \
int *i, int j, char *value)
{
	char	*new_expanded;

	new_expanded = replace_variable(*expanded, value, *i, j + 1);
	if (!new_expanded)
	{
		free(value);
		return ;
	}
	free(*expanded);
	*expanded = new_expanded;
	*i += ft_strlen(value) - 1;
	free(value);
}

void	expand_variable(t_node *current, char **env)
{
	char	*str;

	if (!current || !env)
		return ;
	str = NULL;
	if (current->state == 2 || current->state == 1)
	{
		str = ft_strdup(current->content);
		if (!str)
			return ;
	}
	else if (current->state == 3)
	{
		str = ft_strdup(current->content);
		return ;
	}
	if (str)
	{
		set_expanded(&(str), &(current->content), env);
		// if (current->content[0] == '\0')
		// {
		// 	current->type = 12;
		// }
		free(str);
	}
}
