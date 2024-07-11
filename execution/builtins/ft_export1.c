/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/11 03:32:57 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// export correct=correct wrong%=wrong;export | grep correct;export | grep wrong@export correct=correct wrong%=wrong
// export wrong%=wrong correct=correct; export | grep correct; export | grep wrong@export wrong%=wrong correct=correct
// export a=c;export

static int is_valid(char c)
{
    return((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || ( c >= '0' && c <= '9') || (c == '_'));
}
static int valid_key(char *var)
{
    int i = 0;
    if(!(var[i] >= 'a' && var[i] <= 'z') && !(var[i] >= 'A' && var[i] <= 'Z') && var[i] != '_')
        return(0);
    while(var[i])
    {
        if(!is_valid(var[i]))
            return(0);
        i++;
    }
    return(1);
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
        char *arg = (*command)->arg[i];
        char *equal = strchr(arg, '=');
        if (equal == NULL)
        {
            // Si aucun signe égal n'est trouvé, considérer cela comme une erreur
            //fprintf(stderr, "ft_export: '%s': not a valid identifier\n", arg);
            if(!valid_key(arg))
                fprintf(stderr, "Minishell: `%s': not a valid identifier\n", arg);  
            i++;
            continue;
        }
        size_t key_len = equal - arg;
        char *key = malloc(key_len + 1);
        strncpy(key, arg, key_len);
        key[key_len] = '\0';

        if (!valid_key(key))
        {
            fprintf(stderr, "ft_export: '%s': not a valid identifier\n", arg);
            free(key);
            i++;
            continue;
        }
        char *value = equal + 1;
        // Vérifier si la variable existe déjà dans l'environnement
        t_env *current = *envp;
        while (current != NULL)
        {
            if (strcmp(current->var, key) == 0)
            {
                // Si la variable existe, mettre à jour sa valeur
                free(current->value);
                current->value = strdup(value);
                free(key);
                break;
            }
            current = current->next;
        }
        if (current == NULL)
        {
            // Si la variable n'existe pas, l'ajouter à l'environnement
            t_env *new_env = malloc(sizeof(t_env));
            new_env->var = key;
            new_env->value = strdup(value);
            new_env->next = *envp;
            *envp = new_env;
        }
        i++;
    }
}