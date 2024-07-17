/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:17:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/17 15:32:47 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void expand_home_directory(t_node *current)
{
    if (!current || !current->content)
        return;

    char *new_content = NULL;

    if (current->content[0] == '~' && current->content[1] == '\0')
    {
        new_content = ft_strdup(getenv("HOME"));
    }
    else if (current->content[0] == '~' && current->content[1] == '/' && current->content[2] == '\0')
    {
        //new_content = ft_strdup(ft_strjoin(getenv("HOME"), "/"));
        char *home = getenv("HOME");
        if (home)
        {
            new_content = ft_strjoin(home, "/");
        }
    }

    if (new_content)
    {
        free(current->content);
        current->content = new_content;
        printf("%s\n", current->content);
    }

}
