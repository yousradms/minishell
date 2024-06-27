/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/26 18:05:05 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **ft_split(char *str)
{
    int i = 0;
    int i2 = 0;
    int i3;
    char **tab;
    char quote = 0;

    tab = malloc(sizeof(char *) * w_count);
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
                    tab[i2][i3++] = str[i];
                }
                else if (str[i] == quote)
                {
                    quote = 0;
                    tab[i2][i3++] = str[i];
                }
                else
                {
                    tab[i2][i3++] = str[i];
                }
                i++;
            }
            tab[i2][i3] = '\0';
            i2++;
        }
        else if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            // Skip over spaces marked by delimiters
            if (i > 0 && str[i - 1] == '\x1F')
            {
                i++; // Skip the space
            }
            else
            {
                while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i] != '\0')
                {
                    tab[i2] = malloc(sizeof(char) * 2);
                    tab[i2][0] = str[i];
                    tab[i2][1] = '\0';
                    i2++;
                    i++;
                }
            }
        }
        else
        {
            i++;
        }
    }
    tab[i2] = NULL;
    return (tab);
}
