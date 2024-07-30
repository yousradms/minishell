/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:16:59 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/28 20:17:28 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

void cd_previous(t_env **envp)
{
	char *prev_dir;
	t_env *current;
	
	prev_dir = NULL;
	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->var, "OLDPWD") == 0)
		{
			prev_dir = current->value;
			break;
		}
		current = current->next;
	}
	if (prev_dir)
	{
		if (chdir(prev_dir) == -1)
			perror("cd");
		else
			printf("%s\n", prev_dir);
	}
	else
		fprintf(stderr, "OLDPWD not set\n");
}

void cd_to_dir(const char *dir)
{
	if (chdir(dir) == -1)
		perror("cd");
}

void cd_home(const char *home)
{
	if (chdir(home) == -1)
		perror("cd");
}

int get_current_directory(char *dir, size_t size)
{
	if (getcwd(dir, size) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	return (0);
}
