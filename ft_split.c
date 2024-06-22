/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/22 13:40:45 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_split(char *str)
{
    int i;
    int i2;
    int i3;
    char **tab;
    char quote;
    
    i = 0;
    i2 = 0;
    i3 = 0;
    quote = 0;
    tab = malloc(sizeof(char *) * w_count);
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    while (str[i])
    {
        if (str[i] > 32 || quote)
        {
            i3 = 0;
            tab[i2] = malloc(sizeof(char) * L_count);
            while ((str[i] > 32 || quote) && str[i] != '\0')
            {
                if ((str[i] == '"' || str[i] == '\'') && (quote == 0))
                {
                    quote = str[i];
                    tab[i2][i3++] = str[i]; // conserve la quote
                }
                else if (str[i] == quote)
                {
                    quote = 0;
                    tab[i2][i3++] = str[i]; // conserve la quote
                }
                else 
                    tab[i2][i3++] = str[i];
                i++;
            }
            tab[i2][i3] = '\0';
            i2++;
        }
        else 
            i++;
    }
    tab[i2] = 0;
    return (tab);
}
