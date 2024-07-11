/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 04:30:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/11 05:31:19 by ksellami         ###   ########.fr       */
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
        printf("declare -x %s=\"%s\"\n", current->var, current->value);
        current = current->next;
    }
}
static int	check_arg(char *str)
{
	int	i = 0;

	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] && str[i] != '+' && str[i] != '=')
		return (0);
	return (1);
}

static char *get_key(char *line)
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

static char *get_value(char *line)
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
            fprintf(stderr, "Minishell: `%s': not a valid identifier\n", (*command)->arg[i]);  
        }
        else
        {
            char *key = get_key((*command)->arg[i]);
            char *value = get_value((*command)->arg[i]);
            
            // Check if the key already exists in the environment
            t_env *tmp = *envp;
            int found = 0;
            while (tmp)
            {
                if (!strcmp(key, tmp->var))
                {
                    found = 1;
                    if (value || strchr((*command)->arg[i], '='))
                    {
                        if (strchr((*command)->arg[i], '+'))
                            tmp->value = ft_strjoin(tmp->value, value);
                        else
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