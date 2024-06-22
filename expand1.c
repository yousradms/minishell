/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:36:35 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/22 17:54:00 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//$aaaa
char *remove_quotes(char *s)
{
    char *token;
    int i;
    int j;

    token = malloc(ft_strlen(s) + 1);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
            i++;
        else
            token[j++] = s[i++];
    }
    token[j] = '\0';
    return (token);
}

int contain_env(char *s)
{
    int i;
    
    i = 0;
    while(s[i])
    {
        if(s[i] == '$' && s[i+1] != ' ')
            return(1);
        i++;
    }
    return(0);
}

char *get_env_value(char *var_name)
{
    char *value;

    value = getenv(var_name);
    if (value)
        return strdup(value);
    else
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

void set_value(int *i,int *j,char **var_name,char **expanded)
{
    char *value;
    char *new_expanded;

    value = get_env_value(*var_name);
    if (value != NULL)
    {
        new_expanded = replace_variable(*expanded, value, *i, *j);
        free(*expanded);
        (*expanded) = new_expanded;
        (*i) += strlen(value);
        free(value);
    }
}

void set_expanded(char **str, char **content)
{
    char *expanded;
    int i;
    int j;
    size_t var_length;
    char *var_name;
    
    expanded = strdup(*str);
    i = 0;
    while (expanded[i] != '\0')
    {
        if (expanded[i] == '$')
        {
            j = i + 1;
            while (expanded[j] != '\0' && expanded[j] != ' ' && expanded[j] != '$') 
                j++;
            var_length = j - i - 1;
            var_name = malloc(var_length + 1);
            strncpy(var_name, expanded + i + 1, var_length);
            var_name[var_length] = '\0';
            set_value(&i, &j, &var_name, &expanded);
            free(var_name);
            i = j;
        }
        else 
            i++;  
    }
    free(*content);
    *content = expanded;
}

void expanding(t_node *list)
{
    t_node *current;
    char *str;
    int enter = 0;
    
    current = list;
    while (current!= NULL) 
    {
        if (current->type == 9 && contain_env(current->content))
        {
            str = NULL;
            if (current->state == 2)
                str = remove_quotes(current->content);
            else if (current->state == 1)
                str = current->content;
            else if (current->state == 3)
            {
                current->content = remove_quotes(current->content);
                printf("%s",current->content); 
                break;
            }
            set_expanded(&str,&(current->content));
            printf("%s", current->content);
            enter++;
        }
        
        current = current->next;
    }
    if(enter > 0)
        printf("\n");
}
