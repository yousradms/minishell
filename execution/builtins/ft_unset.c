/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:03:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/06 20:07:07 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void ft_unset(char *var_names[], int num_vars, t_env **envp)
{
    // t_command **cmd = NULL;
    int i = 0;
    while ( i < num_vars )
    {
        char *var_name = var_names[i];
        t_env *current = *envp;
        t_env *prev = NULL;

        while (current != NULL) {
            if (strcmp(current->var, var_name) == 0)
            {
                if (prev == NULL) {
                    *envp = current->next;
                } else {
                    prev->next = current->next;
                }

                free(current->var);
                free(current->value);
                free(current);

                // printf("Unset %s\n", var_name); // Debug statement

                // Break out of the loop after successfully unsetting the variable
                break;
            }

            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            // printf("Variable '%s' not found in environment\n", var_name);
        }
        i++;
    }
    // ft_env(cmd, envp);
}