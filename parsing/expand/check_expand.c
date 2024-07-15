/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:14:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/15 16:18:13 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

int contain_env(char *s)
{
    int i;
    
    i = 0;
    while(s[i]) {
        if(s[i] == '$' && s[i+1] != ' ' && s[i+1] != '^' && s[i+1] != '%' && s[i+1] != '+' && s[i+1] != '~')
            return (1);
        i++;
    }
    return (0);
}

int is_valid_char(char c)
{
    return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') );
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

