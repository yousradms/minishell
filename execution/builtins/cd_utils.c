/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:16:59 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:04:07 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	change_directory(char *prev_dir)
{
	if (chdir(prev_dir) == -1)
	{
		perror("cd");
		return (1);
	}
	else
	{
		printf("%s\n", prev_dir);
		return (0);
	}
}

int	cd_previous(t_env **envp)
{
	char	*prev_dir;
	t_env	*current;
	int		status;

	prev_dir = NULL;
	current = *envp;
	status = 0;
	while (current)
	{
		if (ft_strcmp(current->var, "OLDPWD") == 0)
		{
			prev_dir = current->value;
			break ;
		}
		current = current->next;
	}
	if (prev_dir)
		status = change_directory(prev_dir);
	else
	{
		write(2, "OLDPWD not set\n", 16);
		status = 1;
	}
	return (status);
}

int	cd_to_dir(const char *dir)
{
	int	status;

	status = 0;
	if (chdir(dir) == -1)
	{
		perror("cd");
		status = 1;
	}
	return (status);
}

int	cd_home(const char *home)
{
	int	status;

	status = 0;
	if (chdir(home) == -1)
	{
		perror("cd");
		status = 1;
	}
	return (status);
}

int	get_current_directory(char *dir, size_t size)
{
	if (getcwd(dir, size) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	return (0);
}
