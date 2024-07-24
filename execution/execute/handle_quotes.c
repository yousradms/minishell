/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:04:15 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 13:04:08 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void handle_quotes_ex(t_command **cmd)
{
    t_command *first;
    int i;
    char *cleaned_arg;

    first = *cmd;
    while (first)
    {
        i = 0;
        while (first->arg[i])
        {
            cleaned_arg = first->arg[i];
            if (strchr(first->arg[i], '\'') && strchr(first->arg[i], '\"'))
            {
                char *single_quote_pos = strchr(first->arg[i], '\'');
                char *double_quote_pos = strchr(first->arg[i], '\"');

                if (single_quote_pos < double_quote_pos)
                {
                    // Simple quotes before double quotes, remove simple quotes
                    cleaned_arg = remove_squotes(first->arg[i]);
                }
                else
                {
                    // Double quotes before simple quotes, remove double quotes
                    cleaned_arg = remove_dquotes(first->arg[i]);
                }
                free(first->arg[i]);
                first->arg[i] = cleaned_arg;
            }
            else if (strchr(first->arg[i], '\''))
            {
                cleaned_arg = remove_squotes(first->arg[i]);
                free(first->arg[i]);
                first->arg[i] = cleaned_arg;
            }
            else if (strchr(first->arg[i], '\"'))
            {
                cleaned_arg = remove_dquotes(first->arg[i]);
                free(first->arg[i]);
                first->arg[i] = cleaned_arg;
            }
            i++;
        }
        first = first->next;
    }
}


