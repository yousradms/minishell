/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:51:25 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/25 15:22:58 by ksellami         ###   ########.fr       */
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

int	handle_cd_arguments(t_command **command, t_env **envp, int *status)
{
	char	*home;

	home = getenv("HOME");
	if ((*command)->arg[1] && ft_strlen((*command)->arg[1]) == 0)
		return (0);
	if (!(*command)->arg[1])
	{
		cd_home(home);
		return (1);
	}
	else if (ft_strcmp((*command)->arg[1], "-") == 0)
		*status = cd_previous(envp);
	else
		*status = cd_to_dir((*command)->arg[1]);
	return (1);
}

void	ft_cd(t_command **command, t_env **envp)
{
	char	cwd[1024];
	char	oldpwd[1024];
	int		status;

	status = 0;
	if (get_current_directory(oldpwd, sizeof(oldpwd)) == -1)
	{
		exit_s(1, 1);
		return ;
	}
	if (!handle_cd_arguments(command, envp, &status))
		exit_s(status, 1);
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
