/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:09:19 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/17 15:17:21 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

char *extract_variable_name(char *expanded, int i, int j)
{
    size_t var_length;
    char *var_name;
    
    var_length = j - i - 1;
    var_name = malloc(var_length + 1);
    if(!var_name)
        return(NULL);
    strncpy(var_name, expanded + i + 1, var_length);
    var_name[var_length] = '\0';
    return var_name;
}

// void replace_numeric_variable(char **expanded, int *i, int j)
// {
//     *expanded = replace_variable(*expanded, "", *i, j + 1);
//     *i += 1;
// }
void replace_numeric_variable(char **expanded, int *i, int j)
{
    char *new_expanded = replace_variable(*expanded, "", *i, j + 1);
    if (!new_expanded)
    {
        //fprintf(stderr, "Memory allocation failed in replace_numeric_variable\n");
        return;
    }
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



static void handle_special_cases(char **expanded, int *i, int *j, char **env)
{

    
        if (!expanded || !*expanded || !i || !j || !env)
    {
        //printf("handle_special_cases: Invalid arguments\n"); // Debug statement
        return;
    }
    char *new_expanded;
    char *value = NULL;

    if ((*expanded)[*i + 1] == '0')
    {
        value = ft_strdup("Minishell");
    }
    else if ((*expanded)[*i + 1] == '*')
    {
        value = ft_strdup("");  // For simplicity, we assume empty string for $*
    }
    else if ((*expanded)[*i + 1] == '@')
    {
        value = ft_strdup("");  // For simplicity, we assume empty string for $@
    }
    else if ((*expanded)[*i + 1] == '#')
    {
        value = ft_strdup("0");  // Placeholder, should be the number of positional parameters
    }

    else if ((*expanded)[*i + 1] == '!')
    {
        value = ft_strdup("0");  // Placeholder, should be the process ID of the last background command
    }
    else if ((*expanded)[*i + 1] == '-')
    {
        value = ft_strdup("himBH");  // Placeholder, should be the process ID of the last background command
    }
    else if(((*expanded)[*i + 1] > '0' && (*expanded)[*i + 1] <= '9') && (*expanded)[*i + 2])
    {
        replace_numeric_variable(expanded,i,*j);//leaks here
    }

    else
    {
        process_variable(expanded, i, j, env);
        return;
    }
    if (value)
    {
        new_expanded = replace_variable(*expanded, value, *i, *j + 1);
        if (!new_expanded)
        {
            free(value);
            return; // Memory allocation failed
        }
        free(*expanded);
        *expanded = new_expanded;
        *i += ft_strlen(value) - 1;
        free(value);
    }
}
void set_expanded(char **str, char **content, char **env)
{
    if (!str || !*str || !content || !env)
        return;

    char *expanded;
    int i;
    int j;


    expanded = ft_strdup(*str);
    if(!expanded)
        return ;
    i = 0;
    while (expanded[i] )
    {
        if (expanded[i] == '$')
        {
            j = i + 1;
            handle_special_cases(&expanded, &i, &j, env);
            if (strcmp(expanded,"") == 0)
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
    if (current->state == 2)
    {
        str = ft_strdup(current->content);
        if(!str)
            return ;
    }
    else if (current->state == 1)
    {
        str = ft_strdup(current->content);
        if(!str)
            return ;
    }
    else if (current->state == 3)
    {
        temp = remove_squotes(current->content);
        free(current->content);
        current->content = temp;
        return;
    }
    if(str)
    {
        set_expanded(&str, &(current->content), env);
        free(str);
    }
}