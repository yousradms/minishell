/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 12:08:33 by ydoumas          ###   ########.fr       */
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

	home = get_home_from_env(envp);
	if ((*command)->arg[1] && ft_strlen((*command)->arg[1]) == 0)
		return (0);
	if (!(*command)->arg[1])
	{
		if (home)
			return (cd_home(home));
		else
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			*status = 1;
			return (1);
		}
	}
	else if (ft_strcmp((*command)->arg[1], "-") == 0)
		*status = cd_previous(envp);
	else
		*status = cd_to_dir((*command)->arg[1]);
	return (1);
}

char	*get_home_from_env(t_env **envp)
{
	t_env	*current;

	current = *envp;
	while (current)
	{
		if (strcmp(current->var, "HOME") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
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
		handle_cd_error(1);
		return ;
	}
	if (!handle_cd_arguments(command, envp, &status))
	{
		ex = exit_s(status, 1);
		free(ex);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_directories(envp, oldpwd, cwd);
	else
	{
		perror("getcwd");
		status = 1;
	}
	ex = exit_s(status, 1);
	free(ex);
}
