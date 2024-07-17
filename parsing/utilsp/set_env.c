/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/17 14:39:28 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

char **set_env(char **env)
{
    int i;
    int num_strings;
    char **envp;
    
    i = 0;
    num_strings = 0;
    while (env[num_strings] != NULL)
        num_strings++;
    envp = (char **)malloc(sizeof(char *) * (num_strings + 1));
    if (envp == NULL)
        return (NULL);
    while (i < num_strings)
    {
        envp[i] = ft_strdup(env[i]);
        if (envp[i] == NULL)
        {
            // Free previously allocated memory if strdup fails
            while (i > 0)
            {
                free(envp[i - 1]);
                i--;
            }
            free(envp);
            return NULL;
        }
        i++;
    }
    envp[num_strings] = NULL;
    return (envp);
}
