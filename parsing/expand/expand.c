/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/28 17:41:34 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

char *get_env_value(char *var_name, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (strncmp(env[i], var_name, ft_strlen(var_name)) == 0 && env[i][ft_strlen(var_name)] == '=')
            return ft_strdup(env[i] + ft_strlen(var_name) + 1);
        i++;
    }
    return (NULL);
}


char *replace_variable( char *expanded,  char *value, int i, int j)
{
    size_t len_expanded = strlen(expanded);
    size_t len_value = strlen(value);
    size_t new_len = len_expanded - (j - i) + len_value;

    char *new_expanded = malloc(new_len + 1); // +1 for null terminator
    if (!new_expanded)
        return NULL;

    // Copy part before the variable
    strncpy(new_expanded, expanded, i);
    // Copy the value
    strcpy(new_expanded + i, value);
    // Copy part after the variable
    strcpy(new_expanded + i + len_value, expanded + j);

    return new_expanded;
}

void set_value(int *i, int *j, char **var_name, char **expanded, char **env)
{
    char *value;
    char *new_expanded;

    value = get_env_value(*var_name, env);
    if (value != NULL)
    {
        new_expanded = replace_variable(*expanded, value, *i, *j);
        if (!new_expanded)
        {
            free(value);
            return;
        }
        free(*expanded);
        *expanded = new_expanded;
        *i += ft_strlen(value);
        free(value);
    }
    else
    {
        new_expanded = replace_variable(*expanded, "", *i, *j);
        if(!new_expanded)
            return ;
        free(*expanded);
        *expanded = new_expanded;
        *i += 1;
    }
}


void expanding(t_node *list, char **env)
{
    // print_list(list);
    // exit(1);
    if(!list)
        return;
    t_node *current;
    int in_herdoc;
    
    in_herdoc = 0;
    current = list;
    while (current != NULL)
    {
        if (current->type == 6)
        {
            in_herdoc = 1;
            // Skip spaces after the heredoc
            while (current->next && current->next->type == 1)
                current = current->next;
        }
        if (current == NULL)
            break;
        while(current && current->type == 1)
            current = current->next;
        if (current == NULL)
            break; // Added null check
        if (in_herdoc && current->next)
            current = current->next;
        if ((current->type == 9 || current->type == 8) && contain_env(current->content) && in_herdoc != 1)
            expand_variable(current, env);
        else if (current->type == 9 && contain_home_after_quote(current->content))
            expand_home_directory(current);
        current = current->next;
        in_herdoc = 0;
    }
}



