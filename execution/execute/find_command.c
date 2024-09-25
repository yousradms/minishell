/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:41:44 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/24 10:52:05 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

char	*strjoin(char *str1, char *str2)
{
	int		len1;
	int		len2;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	result = malloc(len1 + len2 + 2);
	if (!result)
		return (NULL);
	ft_strcpy(result, str1);
	result[len1] = '/';
	ft_strcpy(result + len1 + 1, str2);
	return (result);
}

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
	part_path = strjoin(dir, "/");//ft_strjoin
	if (!part_path)
		return (NULL);
	full_path = strjoin(part_path, cmd);
	free(part_path);
	return (full_path);
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
		exit_s(127, 1);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		exit(127);
	}
	i = 0;
	while (paths[i])
	{
		path = build_full_path(paths[i], cmd);
		if (!path)
			return (free_paths(paths), NULL);
		if (access(path, F_OK) == 0)
			return (free_paths(paths), path);
		free(path);
		i++;
	}
	return (free_paths(paths), NULL);
}
