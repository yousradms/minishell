/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:41:44 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/12 18:46:16 by ksellami         ###   ########.fr       */
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

// static char	**get_paths_from_env(char **envp)
// {
// 	int	i;
// 	char **error = NULL;

// 	if (!envp || !(*envp))
// 		return (NULL);
// 	*error = "3";
// 	i = 0;
// 	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
// 		i++;
// 	if (!envp[i])
// 		return (error);
// 	return (ft_split4(envp[i] + 5, ':'));
// }

static char	**get_paths_from_env(char **envp)
{
	int		i;

	if (!envp || !(*envp))
		return (NULL);  // If envp is NULL or empty, return NULL

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;  // Look for the PATH variable in envp
	if (!envp[i])
		return (NULL);  // If no PATH is found, return NULL

	return (ft_split4(envp[i] + 5, ':'));  // Split the PATH string
}


static char	*build_full_path(char *dir, char *cmd)
{
	char	*part_path;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	part_path = strjoin(dir, "/");
	if (!part_path)
		return (NULL);
	full_path = strjoin(part_path, cmd);
	free(part_path);
	return (full_path);
}


#include <sys/stat.h>
// char	*find_commande(char *cmd, char **envp)
// {
// 	int		i;
// 	char	**paths;
// 	char	*path;
// 	struct stat filestat;

// 	if (!cmd || ft_strcmp(cmd, "") == 0)
// 		return (NULL);
	
// 	if (is_absolute_or_relative_path(cmd))
// 	{
// 		if(cmd[0] == '/')
// 		{
// 			if(stat(cmd, &filestat) == 0)
// 			{
// 				if(S_ISDIR(filestat.st_mode))
// 				{
// 					fprintf(stderr, "minishell: %s: is a directory\n", cmd);
// 					cmd = "1";
// 					return(cmd);
// 				}
// 				if(access(cmd, X_OK) == 0)
// 					return (cmd);
// 				else
// 				{
// 					fprintf(stderr, "minishell: %s: No such file or directory\n", cmd);
// 					cmd = "2";
// 					return(cmd);
// 				}
				
// 			}
// 			else
// 			{
// 				fprintf(stderr, "minishell: %s: No such file or directory\n", cmd);
// 				cmd = "2";
// 				return(cmd);
// 			}
			
// 		}
// 		else
// 		{
// 			return(cmd);
// 		}
// 	}
// 	paths = get_paths_from_env(envp);
// 	if (!paths)
// 		return (NULL);
// 	if(ft_strcmp(*paths, "3") == 0)
// 	{
// 		// fprintf(stderr, "minishell: No such file or directory\n");
// 		return("3");
// 	}
// 	i = 0;
// 	while (paths[i])
// 	{
// 		path = build_full_path(paths[i], cmd);
// 		if (!path)
// 			return (free_paths(paths), NULL);
// 		if (access(path, F_OK) == 0)
// 			return (free_paths(paths), path);
// 		free(path);
// 		i++;
// 	}
// 	return (free_paths(paths), NULL);
// }

char	*find_commande(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;
	struct stat filestat;

	if (!cmd || ft_strcmp(cmd, "") == 0)
		return (NULL);

	if (is_absolute_or_relative_path(cmd))
	{
		if (cmd[0] == '/')
		{
			if (stat(cmd, &filestat) == 0)
			{
				if (S_ISDIR(filestat.st_mode))
				{
					fprintf(stderr, "minishell: %s: is a directory\n", cmd);
					return ("1");  // Indicate that the command is a directory
				}
				if (access(cmd, X_OK) == 0)
					return (cmd);  // Command is executable
				else
				{
					fprintf(stderr, "minishell: %s: No such file or directory\n", cmd);
					return ("2");  // Command file not found or not accessible
				}
			}
			else
			{
				fprintf(stderr, "minishell: %s: No such file or directory\n", cmd);
				return ("2");  // Command file does not exist
			}
		}
		else
		{
			return (cmd);  // Handle relative path
		}
	}

	// Get the paths from environment variables
	paths = get_paths_from_env(envp);
	if (!paths)
	{
		// fprintf(stderr, "minishell: No such file or directory\n");
		return ("3");  // Handle the case where PATH is not found
	}

	// Iterate through paths and check for command existence
	i = 0;
	while (paths[i])
	{
		path = build_full_path(paths[i], cmd);
		if (!path)
		{
			free_paths(paths);
			return (NULL);  // Memory allocation failed
		}
		if (access(path, F_OK) == 0)
		{
			free_paths(paths);
			return (path);  // Command found
		}
		free(path);
		i++;
	}

	free_paths(paths);
	return (NULL);  // Command not found
}

