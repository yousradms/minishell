/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/15 18:09:29 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"


static int ft_isalpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
static int ft_isalnum(char c)
{
    return(ft_isalpha(c) || (c >= '0' && c <= '9'));
}
static void get_expoted(t_env **envp)
{
    t_env *current;
    current = *envp;
    while (current != NULL)
    {
        //printf("declare -x %s=\"%s\"\n", current->var, current->value);
        printf("declare -x %s",current->var);
        if(current->value != NULL)

            printf("=\"%s\"\n",current->value);
        else
            printf("\n");
        current = current->next;
    }
}

static int is_valid(char c)
{
    return(ft_isalnum(c) || c == '_');
}
static int check_arg(char *var)
{
    int i = 0;
    if(!(ft_isalpha(var[i]) || var[i] == '_'))
        return (0);
    while(var[i] && var[i] != '=' && var[i] != '+')
    {
        if(!is_valid(var[i]))
            return (0);
        i++;
    }
    if(var[i] && var[i] != '+' && var[i] != '=')
        return (0);
    return (1);
}

static char *extract_var(char *line)
{
    int i = 0;
    int key_len = 0;
    while (line[i] && line[i] != '=' && line[i] != '+')
    {
        key_len++;
        i++;
    }
    char *key = (char *)malloc(sizeof(char) * (key_len + 1));
    i = 0;
    int j = 0;
    while (line[i] && line[i] != '=' && line[i] != '+')
    {
        key[j++] = line[i++];
    }
    key[j] = '\0';
    return key;
}

static char *extract_value(char *line)
{
    int i = 0;
    while (line[i] && line[i] != '=')
        i++;
    if (!line[i])
        return NULL;
    i++;
    int value_len = 0;
    while (line[i])
    {
        value_len++;
        i++;
    }
    char *value = (char *)malloc(sizeof(char) * (value_len + 1));
    i = 0;
    int j = 0;
    while (line[i] && line[i] != '=')
        i++;
    if (line[i])
        i++;
    while (line[i])
    {
        value[j++] = line[i++];
    }
    value[j] = '\0';
    return value;
}

void ft_export(t_command **command, t_env **envp)
{
    int i;
    
    // If no arguments are provided, print the current environment
    if ((*command)->arg[1] == NULL)
    {
        
        get_expoted(envp);
        return ;
    }
    i = 1;
    while ((*command)->arg[i] != NULL)
    {
        if (!check_arg((*command)->arg[i]))
        {
            //printf("enter here\n");
            fprintf(stderr, "Minishell: `%s': not a valid identifier\n", (*command)->arg[i]);  
        }
        else
        {
            char *key = extract_var((*command)->arg[i]);
            char *value = extract_value((*command)->arg[i]);
            // Check if the key already exists in the environment
            t_env *tmp = *envp;
            int found = 0;
            while (tmp)
            {
                if (!strcmp(key, tmp->var))
                {
                    found = 1;
                    if (strchr((*command)->arg[i], '+') && strchr((*command)->arg[i], '='))
                    {
                        // If the argument contains "+=", concatenate the existing value with the new value
                        char *new_value = ft_strjoin(tmp->value, value);
                        free(tmp->value);
                        tmp->value = new_value;
                    }
                        else if (strchr((*command)->arg[i], '='))
                    {
                        // If the argument contains "=", replace the existing value with the new value
                        free(tmp->value);
                        tmp->value = strdup(value);
                    }
                    break;
                }
                tmp = tmp->next;
            }
            
            // If the key doesn't exist, add a new entry to the environment
            if (!found)
            {
                t_env *new_env = (t_env *)malloc(sizeof(t_env));
                new_env->var = strdup(key);
                new_env->value = value ? strdup(value) : NULL;
                new_env->next = *envp;
                *envp = new_env;
            }
            free(key);
            free(value);
        }
        i++;
    }
}