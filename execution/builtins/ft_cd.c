/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/19 12:34:10 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

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

void	ft_cd(t_command **command, t_env **envp)
{
	char	cwd[1024];
	char	*home;
	char	oldpwd[1024];
	int status = 0;

	home = getenv("HOME");
	if (get_current_directory(oldpwd, sizeof(oldpwd)) == -1)
	{
		exit_s(1, 1);
		return ;
	}
	if ((*command)->arg[1] && ft_strlen((*command)->arg[1]) == 0)
	{
		exit_s(0, 1);
		return ;
	}
	if (!(*command)->arg[1])
	{
		exit_s(0, 1);
		cd_home(home);
	}
	else if (ft_strcmp((*command)->arg[1], ".") != 0)
	{
		if (ft_strcmp((*command)->arg[1], "-") == 0)
			status = cd_previous(envp);
		else
			status = cd_to_dir((*command)->arg[1]);
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
	exit_s(status, 1);
}
