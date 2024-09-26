/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:14:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:06:29 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	contain_env(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '^' \
		&& s[i + 1] != '%' && s[i + 1] != '+' \
		&& s[i + 1] != '~' && s[i + 1] != '=' \
		&& s[i + 1] != ':' && s[i + 1] != '.' \
		&& s[i + 1] != ',' && s[i + 1] != '`' && \
		s[i + 1] != '/' && s[i + 1] != '\"' && s[i + 1] != '\'')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_char(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || \
	(c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int	contain_home_after_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] && s[i] == '~' && !s[i + 1])
		return (1);
	return (0);
}

char	*handle_specific_cases(char c)
{
	char	*exit_status_str;

	if (c == '0')
		return (ft_strdup("Minishell"));
	else if (c == '*')
		return (ft_strdup(""));
	else if (c == '@')
		return (ft_strdup(""));
	else if (c == '#')
		return (ft_strdup("0"));
	else if (c == '!')
		return (ft_strdup(""));
	else if (c == '-')
		return (ft_strdup("himBH"));
	else if (c == '?')
	{
		exit_status_str = exit_s(0, 0);
		return (exit_status_str);
	}
	return (NULL);
}

void	handle_special_cases(char **expanded, int *i, int *j, char **env)
{
	char	*value;

	if (!validate_inputs(expanded, i, j, env))
		return ;
	value = handle_specific_cases((*expanded)[*i + 1]);
	if (value != NULL)
		replace_special_variable(expanded, i, *j, value);
	else if ((*expanded)[*i + 1] > '0' && \
	(*expanded)[*i + 1] <= '9' && (*expanded)[*i + 2])
		replace_numeric_variable(expanded, i, *j);
	else
		process_variable(expanded, i, j, env);
}
