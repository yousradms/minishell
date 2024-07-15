/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/13 21:49:28 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"
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

// void export_env(t_env *head)
// {
//     while (head)
//     {
//         if (head->value)
//             printf("declare -x %s=\"%s\"\n", head->var, head->value);
//         head = head->next;
//     }
// }

void ft_env1(t_command **command, t_env **envp)
{
	(void)command; // Suppress unused parameter warning
	t_env *env; // Dereference envp to get the linked list head
	
	env = *envp;
	if (env == NULL)
		return;
	// Iterate through the linked list of environment variables
	while (env != NULL)
	{
		 printf("declare -x %s=\"%s\"\n", env->var, env->value);
		env = env->next; // Move to the next node
	}
}

void ft_export(t_command **command, t_env **envp, char **str) {
    int i = 1;
    if(!str || !str[0])
    {
        ft_env1(command ,envp);
        return ;
    }
    while ((*command)->arg[i] != NULL) {
        char *arg = (*command)->arg[i];
        char *equal = strchr(arg, '=');

        if (equal == NULL) {
            // Si aucun signe égal n'est trouvé, considérer cela comme une erreur
            fprintf(stderr, "ft_export: '%s': not a valid identifier\n", arg);
            i++;
            continue;
        }

        size_t key_len = equal - arg;
        char *key = malloc(key_len + 1);
        strncpy(key, arg, key_len);
        key[key_len] = '\0';

        if (!valid_key(key)) {
            fprintf(stderr, "ft_export: '%s': not a valid identifier\n", arg);
            free(key);
            i++;
            continue;
        }

        char *value = equal + 1;

        // Vérifier si la variable existe déjà dans l'environnement
        t_env *current = *envp;
        while (current != NULL) {
            if (strcmp(current->var, key) == 0) {
                // Si la variable existe, mettre à jour sa valeur
                free(current->value);
                current->value = strdup(value);
                free(key);
                break;
            }
            current = current->next;
        }

        if (current == NULL) {
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