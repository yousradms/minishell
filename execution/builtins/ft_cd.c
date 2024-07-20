/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/20 10:20:46 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void update_oldpwd(t_env **envp, const char *oldpwd)
{
    t_env *current = *envp;
    while (current) {
        if (strcmp(current->var, "OLDPWD") == 0) {
            free(current->value);
            current->value = strdup(oldpwd);
            return;
        }
        current = current->next;
    }
}

static void update_pwd(t_env **envp, const char *newpwd)
{
    t_env *current = *envp;
    while (current) {
        if (strcmp(current->var, "PWD") == 0) {
            free(current->value);
            current->value = strdup(newpwd);
            return;
        }
        current = current->next;
    }
}

void ft_cd(t_command **command, t_env **envp)
{
    char cwd[1024];
    char *home = getenv("HOME");
    char oldpwd[1024];

    // Get the current working directory before changing
    if (getcwd(oldpwd, sizeof(oldpwd)) == NULL) {
        perror("getcwd");
        return;
    }

    if (!(*command)->arg[1]) {
        // Change to home directory
        if (chdir(home) == -1) {
            perror("cd");
        }
    } else if (strcmp((*command)->arg[1], ".") == 0) {
        // Stay in the current directory
    } else if (strcmp((*command)->arg[1], "-") == 0) {
        // Change to previous directory
        char *prev_dir = NULL;
        t_env *current = *envp;
        while (current) {
            if (strcmp(current->var, "OLDPWD") == 0) {
                prev_dir = current->value;
                break;
            }
            current = current->next;
        }
        if (prev_dir) {
            if (chdir(prev_dir) == -1) {
                perror("cd");
            } else {
                printf("%s\n", prev_dir);
            }
        } else {
            fprintf(stderr, "OLDPWD not set\n");
        }
    } else {
        // Change to specified directory
        if (chdir((*command)->arg[1]) == -1) {
            perror("cd");
        }
    }

    // Update environment variables
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        update_oldpwd(envp, oldpwd); // Set OLDPWD to the old directory
        update_pwd(envp, cwd);        // Set PWD to the new directory
    } else {
        perror("getcwd");
    }
}