/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 20:45:48 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_env(void)
{
	char	*pwd;
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * 6);
	if (!envp)
		return (NULL);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	envp[0] = ft_strjoin("PATH=", \
	"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	envp[1] = ft_strjoin("OLDPWD=", "");
	envp[2] = ft_strjoin("PWD=", pwd);
	envp[3] = ft_strjoin("_=", "/usr/bin/env");
	envp[4] = ft_strjoin("SHLVL=", "1");
	envp[5] = NULL;
	free(pwd);
	return (envp);
}

char	**set_env(char **env)
{
	int		i;
	int		num_strings;
	char	**envp;

	i = 0;
	num_strings = 0;
	while (env[num_strings] != NULL)
		num_strings++;
	envp = (char **)malloc(sizeof(char *) * (num_strings + 1));
	if (envp == NULL)
		return (NULL);
	while (i < num_strings)
	{
		envp[i] = ft_strdup(env[i]);
		if (envp[i] == NULL)
			return (env);
		i++;
	}
	envp[num_strings] = NULL;
	return (envp);
}
