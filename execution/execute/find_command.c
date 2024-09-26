/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:41:44 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/26 12:05:14 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_absolute_or_relative_path(char *cmd)
{
	if (!cmd || ft_strcmp(cmd, "") == 0)
		return (0);
	return (cmd[0] == '/' || cmd[0] == '.');
}

static char	**get_paths_from_env(char **envp)
{
	int		i;

	if (!envp || !(*envp))
		return (NULL);
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split4(envp[i] + 5, ':'));
}

static char	*build_full_path(char *dir, char *cmd)
{
	char	*part_path;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	part_path = ft_strjoin(dir, "/");
	if (!part_path)
		return (NULL);
	full_path = ft_strjoin(part_path, cmd);
	free(part_path);
	return (full_path);
}

void	print_no_such_f_d(char *s)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
}

char	*find_commande(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;

	if (!cmd || ft_strcmp(cmd, "") == 0)
		return (NULL);
	if (is_absolute_or_relative_path(cmd))
		return (cmd);
	paths = get_paths_from_env(envp);
	if (!paths || !(*paths))
	{
		print_no_such_f_d(cmd);
		exit(127);
	}
	i = -1;
	while (paths[++i])
	{
		path = build_full_path(paths[i], cmd);
		if (!path)
			return (free_paths(paths), NULL);
		if (access(path, F_OK) == 0)
			return (free_paths(paths), path);
		free(path);
	}
	return (free_paths(paths), NULL);
}
