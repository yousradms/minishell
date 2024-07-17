/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:55:02 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/04 20:35:59 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_pwd(t_command **command)
{
    (void)command; 
    char cwd[4096]; 
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd); 
    else
        perror("getcwd() error");
}
