/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:09:19 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/28 20:31:09 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

char *extract_variable_name(char *expanded, int i, int j)
{
	int var_length;
	char *var_name;
	
	var_length = j - i - 1;
	var_name = malloc(var_length + 1);
	if (!var_name)
		return(NULL);
	ft_strncpy(var_name, expanded + i + 1, var_length);
	var_name[var_length] = '\0';
	return (var_name);
}

void replace_numeric_variable(char **expanded, int *i, int j)
{
	char *new_expanded;
	
	new_expanded = replace_variable(*expanded, "", *i, j + 1);
	if (!new_expanded)
		return;
	free(*expanded);
	*expanded = new_expanded;
	*i += 1;
}

void process_variable(char **expanded, int *i, int *j, char **env)
{
	int k;
	char *var_name;

	k = *j;
	while ((*expanded)[k] != '\0' && (*expanded)[k] != ' ' && (*expanded)[k] != '$' && is_valid_char((*expanded)[k]))
		k++;
	*j = k;
	var_name = extract_variable_name(*expanded, *i, *j);
	set_value(i, j, &var_name, expanded, env);
	free(var_name);
}

static int validate_inputs(char **expanded, int *i, int *j, char **env)
{
	return (expanded && *expanded && i && j && env);
}
char* exit_s(int new_one, int set)
{
	static int x = 0;
	if (set == 1)
		x = new_one;
	else
		return ft_itoa(x);
	return NULL;
}

static char *handle_specific_cases(char c)
{
	char *exit_status_str;

	if (c == '0')
		return (ft_strdup("Minishell"));
	else if (c == '*')
		return (ft_strdup(""));
	else if (c == '@')
		return (ft_strdup(""));
	else if (c == '#')
		return (ft_strdup("0"));
	else if (c == '!')
		return (ft_strdup("0"));
	else if (c == '-')
		return (ft_strdup("himBH"));
	else if(c == '?')
	{
		exit_status_str = exit_s(0, 0);
		return (exit_status_str);
	}
	return (NULL);
}

static void replace_special_variable(char **expanded, int *i, int j, char *value)
{
	char *new_expanded;

	new_expanded = replace_variable(*expanded, value, *i, j + 1);
	if (!new_expanded)
	{
		free(value);
		return;
	}
	free(*expanded);
	*expanded = new_expanded;
	*i += ft_strlen(value) - 1;
	free(value);
}

static void handle_special_cases(char **expanded, int *i, int *j, char **env)
{
	char *value;

	if (!validate_inputs(expanded, i, j, env))
		return;
	value = handle_specific_cases((*expanded)[*i + 1]);
	if (value)
	{
		replace_special_variable(expanded, i, *j, value);
	}
		
	else if ((*expanded)[*i + 1] > '0' && (*expanded)[*i + 1] <= '9' && (*expanded)[*i + 2])
		replace_numeric_variable(expanded, i, *j);
	else
		process_variable(expanded, i, j, env);
}

void set_expanded(char **str, char **content, char **env)
{
	char *expanded;
	int i;
	int j;
	
	if (!str || !*str || !content || !env)
		return;
	expanded = ft_strdup(*str);
	if (!expanded)
		return ;
	i = 0;
	while (expanded[i])
	{
		if (expanded[i] == '$')
		{
			j = i + 1;
			handle_special_cases(&expanded, &i, &j, env);
			if (ft_strchr(expanded, '$') == NULL || ft_strcmp(expanded, "") == 0)
				break;
		}
		else
			i++;
	}
	free(*content);
	*content = expanded;
}

void expand_variable(t_node *current, char **env)
{
	char *str;
	char *temp;
	
	if (!current || !env)
		return;
	str = NULL;
	if (current->state == 2 || current->state == 1)
	{
		str = ft_strdup(current->content);
		if (!str)
			return ;
	}
	else if (current->state == 3)
	{
		temp = remove_squotes(current->content);
		free(current->content);
		current->content = temp;
		return;
	}
	if (str)
	{
		set_expanded(&str, &(current->content), env);//$? -->replace by x
		free(str);
	}
}

