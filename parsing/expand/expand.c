/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 17:08:52 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char *get_env_value(char *var_name, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (strncmp(env[i], var_name, strlen(var_name)) == 0 && env[i][strlen(var_name)] == '=')
            return strdup(env[i] + strlen(var_name) + 1);
        i++;
    }
    return (NULL);
}

char *replace_variable(char *str, char *value, int start, int end)
{
    int new_expanded_len;
    char *new_expanded;

    new_expanded_len = strlen(str) - (end - start) + strlen(value) + 1;
    new_expanded = malloc(new_expanded_len);
    strncpy(new_expanded, str, start);
    strcpy(new_expanded + start, value);
    strcpy(new_expanded + start + strlen(value), str + end);
    return (new_expanded);
}

void set_value(int *i, int *j, char **var_name, char **expanded, char **env)
{
    char *value;
    char *new_expanded;

    value = get_env_value(*var_name, env);
    if (value != NULL)
    {
        new_expanded = replace_variable(*expanded, value, *i, *j);
        free(*expanded);
        *expanded = new_expanded;
        *i += strlen(value);
        free(value);
    }
    else
    {
        new_expanded = replace_variable(*expanded, "", *i, *j);
        free(*expanded);
        *expanded = new_expanded;
        *i += 1;
    }
}


void expanding(t_node *list, char **env)
{
    t_node *current;
    //int enter;
    int in_herdoc;
    
    //enter = 0;
    in_herdoc = 0;
    current = list;
    while (current != NULL)
    {
        if (current->type == 6)
            in_herdoc = 1;
        if (in_herdoc && current->next)
            current = current->next;
        if (current->type == 9 && contain_env(current->content) && !in_herdoc)
        {
            expand_variable(current, env);
            //enter++;
        }
        else if (current->type == 9 && contain_home_after_quote(current->content))
            expand_home_directory(current);
        current = current->next;
        in_herdoc = 0;
    }
    // if (enter > 0)
    //     printf("\n");
}



