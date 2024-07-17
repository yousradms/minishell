/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 12:01:54 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//chdir-->before change old pwd and after pwd -->env


void ft_cd(t_command **command)
{
    char cwd[1024];

    if ((*command)->arg[1] != NULL)
    {
        if (strcmp((*command)->arg[1], "~") == 0)
        {
            if (chdir(getenv("HOME")) == -1)
            {
                perror("cd");
                return;
            }
        }
        else if (strcmp((*command)->arg[1], "-") == 0)
        {
            if (chdir(getenv("OLDPWD")) == -1)
            {
                perror("cd");
                return;
            }
        }
        else
        {
            // Save current working directory to OLDPWD
            if (getcwd(cwd, sizeof(cwd)) == NULL)
            {
                perror("getcwd");
                return;
            }
            if (setenv("OLDPWD", cwd, 1) == -1)
            {
                perror("setenv");
                return;
            }

            // Change to the new directory
            if (chdir((*command)->arg[1]) == -1)
            {
                perror("cd");
                return;
            }

            // Update PWD to the new current working directory
            if (getcwd(cwd, sizeof(cwd)) == NULL)
            {
                perror("getcwd");
                return;
            }
            if (setenv("PWD", cwd, 1) == -1)
            {
                perror("setenv");
                return;
            }
        }
    }
    else
    {
        if (chdir(getenv("HOME")) == -1)
        {
            perror("cd");
            return;
        }
    }
}
