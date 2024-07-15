/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/15 19:23:10 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"
// static int is_valid(char c)
// {
//     return((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || ( c >= '0' && c <= '9') || (c == '_'));
// }
// static int valid_key(char *var)
// {
//     int i = 0;
//     if(!(var[i] >= 'a' && var[i] <= 'z') && !(var[i] >= 'A' && var[i] <= 'Z') && var[i] != '_')
//         return(0);
//     while(var[i])
//     {
//         if(!is_valid(var[i]))
//             return(0);
//         i++;
//     }
//     return(1);
// }

// // void export_env(t_env *head)
// // {
// //     while (head)
// //     {
// //         if (head->value)
// //             printf("declare -x %s=\"%s\"\n", head->var, head->value);
// //         head = head->next;
// //     }
// // }

// void ft_env1(t_command **command, t_env **envp)
// {
// 	(void)command; // Suppress unused parameter warning
// 	t_env *env; // Dereference envp to get the linked list head
	
// 	env = *envp;
// 	if (env == NULL)
// 		return;
// 	// Iterate through the linked list of environment variables
// 	while (env != NULL)
// 	{
// 		 printf("declare -x %s=\"%s\"\n", env->var, env->value);
// 		env = env->next; // Move to the next node
// 	}
// }

// void ft_export(t_command **command, t_env **envp, char **str) {
//     int i = 1;
//     if(!str || !str[0])
//     {
//         ft_env1(command ,envp);
//         return ;
//     }
//     while ((*command)->arg[i] != NULL) {
//         char *arg = (*command)->arg[i];
//         char *equal = strchr(arg, '=');

//         if (equal == NULL) {
//             // Si aucun signe égal n'est trouvé, considérer cela comme une erreur
//             fprintf(stderr, "ft_export: '%s': not a valid identifier\n", arg);
//             i++;
//             continue;
//         }

//         size_t key_len = equal - arg;
//         char *key = malloc(key_len + 1);
//         strncpy(key, arg, key_len);
//         key[key_len] = '\0';

//         if (!valid_key(key)) {
//             fprintf(stderr, "ft_export: '%s': not a valid identifier\n", arg);
//             free(key);
//             i++;
//             continue;
//         }

//         char *value = equal + 1;

//         // Vérifier si la variable existe déjà dans l'environnement
//         t_env *current = *envp;
//         while (current != NULL) {
//             if (strcmp(current->var, key) == 0) {
//                 // Si la variable existe, mettre à jour sa valeur
//                 free(current->value);
//                 current->value = strdup(value);
//                 free(key);
//                 break;
//             }
//             current = current->next;
//         }

//         if (current == NULL) {
//             // Si la variable n'existe pas, l'ajouter à l'environnement
//             t_env *new_env = malloc(sizeof(t_env));
//             new_env->var = key;
//             new_env->value = strdup(value);
//             new_env->next = *envp;
//             *envp = new_env;
//         }
//         i++;
//     }
// }
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
            fprintf(stderr, "Minishell: %s': not a valid identifier\n", (*command)->arg[i]);  
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