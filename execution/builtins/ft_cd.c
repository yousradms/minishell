/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 09:16:41 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_oldpwd(t_env **envp, char *oldpwd)
{
	t_env	*current;

	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->var, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(oldpwd);
			return ;
		}
		current = current->next;
	}
}

void	update_pwd(t_env **envp, char *newpwd)
{
	t_env	*current;

	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->var, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(newpwd);
			return ;
		}
		current = current->next;
	}
}

int	handle_cd_arguments(t_command **command, t_env **envp, int *status)
{
	char	*home;

	// home = getenv("HOME");
	home = get_home_from_env(envp);
	if ((*command)->arg[1] && ft_strlen((*command)->arg[1]) == 0)
		return (0);
	// if (!(*command)->arg[1])
	// {
	// 	cd_home(home);
	// 	return (1);
	// }
	    if (!(*command)->arg[1]) {
        if (home) {
            return cd_home(home);
        } else {
            // fprintf(stderr, "bash: cd: HOME not set\n");
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			*status = 1;
            return 1; // Error code for HOME not set
        }
    }
	else if (ft_strcmp((*command)->arg[1], "-") == 0)
		*status = cd_previous(envp);
	else
		*status = cd_to_dir((*command)->arg[1]);
	return (1);
}

char *get_home_from_env(t_env **envp)
{
    t_env *current = *envp;

    while (current) {
        if (strcmp(current->var, "HOME") == 0) {
            return current->value; // Return the value of HOME
        }
        current = current->next;
    }
    return NULL; // HOME not found
}
void	ft_cd(t_command **command, t_env **envp)
{
	char	cwd[1024];
	char	oldpwd[1024];
	int		status;
	char	*ex;

	status = 0;
	if (get_current_directory(oldpwd, sizeof(oldpwd)) == -1)
	{
		ex = exit_s(1, 1);
		free(ex);
		return ;
	}
	if (!handle_cd_arguments(command, envp, &status))
	{
		ex = exit_s(status, 1);
		free(ex);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_oldpwd(envp, oldpwd);
		update_pwd(envp, cwd);
	}
	else
	{
		perror("getcwd");
		status = 1;
	}
	ex = exit_s(status, 1);
	free(ex);
}
