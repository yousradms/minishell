/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:04:15 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/22 17:05:26 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// void handle_quotes_ex(t_command **cmd)
// {
//     t_command *first;
//     int i;
//     char *cleaned_arg;

//     first = *cmd;
//     while (first)
//     {
//         i = 0;
//         while (first->arg[i])
//         {
//             cleaned_arg = first->arg[i];
//             if (strchr(first->arg[i], '\'') && strchr(first->arg[i], '\"'))
//             {
//                 char *single_quote_pos = strchr(first->arg[i], '\'');
//                 char *double_quote_pos = strchr(first->arg[i], '\"');

//                 if (single_quote_pos < double_quote_pos)
//                 {
//                     // Simple quotes before double quotes, remove simple quotes
//                     cleaned_arg = remove_squotes(first->arg[i]);
                    
//                 }
//                 else
//                 {
//                     // Double quotes before simple quotes, remove double quotes
//                     cleaned_arg = remove_dquotes(first->arg[i]);
 
//                 }
//                 free(first->arg[i]);
//                 first->arg[i] = cleaned_arg;
//             }
//             else if (strchr(first->arg[i], '\''))
//             {
//                 cleaned_arg = remove_squotes(first->arg[i]);
//                 free(first->arg[i]);
//                 first->arg[i] = cleaned_arg;
//             }
//             else if (strchr(first->arg[i], '\"'))
//             {
//                 cleaned_arg = remove_dquotes(first->arg[i]);
//                 free(first->arg[i]);
//                 first->arg[i] = cleaned_arg;
//             }
//             i++;
//         }
//         first = first->next;
//     }
// }
// void handle_quotes_ex(t_command **cmd)
// {
//     t_command *first;
//     int i;
//     char *cleaned_arg;

//     first = *cmd;
//     while (first)
//     {
//         i = 0;
//         while (first->arg[i])
//         {
//             cleaned_arg = first->arg[i];
//             while (strchr(cleaned_arg, '\'') || strchr(cleaned_arg, '\"'))
//             {
//                 char *single_quote_pos = strchr(cleaned_arg, '\'');
//                 char *double_quote_pos = strchr(cleaned_arg, '\"');

//                 if (single_quote_pos && (!double_quote_pos || single_quote_pos < double_quote_pos))
//                 {
//                     // Single quotes before double quotes or no double quotes, remove single quotes
//                     cleaned_arg = remove_squotes(cleaned_arg);
//                 }
//                 else if (double_quote_pos)
//                 {
//                     // Double quotes before single quotes or no single quotes, remove double quotes
//                     cleaned_arg = remove_dquotes(cleaned_arg);
//                 }
//             }
            
//             // if(first->arg[i])
//             //     free(first->arg[i]);
//             first->arg[i] = cleaned_arg;
//             i++;
//         }
//         first = first->next;
//     }
// }

//l""s'a'""
//"'l''s'"

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
            int len = strlen(cleaned_arg);
            char *result = (char *)malloc(len + 1);
            if(!result)
                return;
            int j = 0, k = 0;
            int single_quote_open = 0, double_quote_open = 0;

            while (cleaned_arg[j])
            {
                if (cleaned_arg[j] == '\'' && !double_quote_open)
                {
                    single_quote_open = !single_quote_open;
                }
                else if (cleaned_arg[j] == '\"' && !single_quote_open)
                {
                    double_quote_open = !double_quote_open;
                }
                else
                {
                    result[k++] = cleaned_arg[j];
                }
                j++;
            }
            result[k] = '\0';

            free(first->arg[i]);
            first->arg[i] = result;
            i++;
        }
        first = first->next;
    }
}




