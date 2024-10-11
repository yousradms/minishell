/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:04:15 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/10 21:39:10 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_single_quote_arg(char *arg)
{
	char	*result;

	result = (char *)malloc(2);
	if (!result)
		return (NULL);
	result[0] = *arg;
	result[1] = '\0';
	return (result);
}

char	*clean_argument(char *arg)
{
	char	*result;
	int		k;
	int		single_quote_open;
	int		double_quote_open;

	result = (char *)malloc(ft_strlen(arg) + 1);
	if (!result)
		return (NULL);
	k = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	if ((ft_strlen(arg) == 1 && (*arg == '\'' || *arg == '\"')))
		return (free(result), handle_single_quote_arg(arg));
	while (*arg)
	{
		if (*arg == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (*arg == '\"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		else
			result[k++] = *arg;
		arg++;
	}
	result[k] = '\0';
	return (result);
}

static void	clean_command_arguments(t_command *cmd)
{
	int		i;
	char	*cleaned_arg;

	i = 0;
	while (cmd->arg[i])
	{
		cleaned_arg = clean_argument(cmd->arg[i]);
		free(cmd->arg[i]);
		cmd->arg[i] = cleaned_arg;
		i++;
	}
}

void	handle_quotes_ex(t_command **cmd)
{
	t_command	*first;

	first = *cmd;
	while (first)
	{
		clean_command_arguments(first);
		first = first->next;
	}
}
