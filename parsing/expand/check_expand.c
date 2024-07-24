/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:14:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/24 17:36:40 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int contain_env(char *s)
{
    int i;
    
    i = 0;
    while(s[i]) {
        if(s[i] == '$' && s[i+1] != ' ' && s[i + 1] != '^' && s[i+1] != '%' && s[i+1] != '+' && s[i+1] != '~')
            return (1);
        i++;
    }
    return (0);
}

int is_valid_char(char c)
{
    return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '?');
}

int contain_home_after_quote(char *s)
{
    int i = 0;

    while(s[i] && s[i] == ' ')
        i++;
    if(s[i] && s[i] == '~')
        return(1);
    return(0);
}


