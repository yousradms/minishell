/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/10 13:00:32 by ksellami         ###   ########.fr       */
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

	home = getenv("HOME");
	if (get_current_directory(oldpwd, sizeof(oldpwd)) == -1)
		return ;
	if (!(*command)->arg[1])
		cd_home(home);
	else if (ft_strcmp((*command)->arg[1], ".") != 0)
	{
		if (ft_strcmp((*command)->arg[1], "-") == 0)
			cd_previous(envp);
		else
			cd_to_dir((*command)->arg[1]);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_oldpwd(envp, oldpwd);
		update_pwd(envp, cwd);
	}
	else
		perror("getcwd");
}
