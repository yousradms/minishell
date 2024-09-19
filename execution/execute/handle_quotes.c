/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:04:15 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/18 21:27:01 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

char	*clean_argument(char *arg)
{
	int		len;
	char	*result;
	int		k;
	int		single_quote_open;
	int		double_quote_open;

	len = ft_strlen(arg);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	k = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	if ((ft_strlen(arg) == 1 && (*arg == '\'' || *arg == '\"')))
	{
		result[0] = *arg;
		result[1] = '\0';
		return (result);
	}
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
