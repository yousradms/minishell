/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:17:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 15:54:43 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void expand_home_directory(t_node *current)
{
    if (current->content[0] == '~' && current->content[1] == '\0')
    {
        current->content = strdup(getenv("HOME"));
        printf("%s\n", current->content);
    } 
    else if (current->content[0] == '~' && current->content[1] == '/' && current->content[2] == '\0') 
    {
        current->content = strdup(ft_strjoin(getenv("HOME"), "/"));
        printf("%s\n", current->content);
    }
}