/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 10:27:40 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char    **get_env(void)
// {
// 	// printf("get this point\n");
//     char    **envp = NULL;
//     char    *pwd;
//     // int     i = 0;

//     // Allocate space for 6 environment variables + NULL terminator
//     envp = (char **)malloc(sizeof(char *) * 6);
//     if (!envp)
//         return (NULL);  // Handle allocation failure

//     pwd = getcwd(NULL, 0);
//     if (!pwd)
//         return (NULL);
//     // Set environment variables
// 	// printf("%s\n", envp[i]);
//     envp[0] = ft_strjoin("PATH=", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
// 	// printf("get this point\n");
// 	// printf("%s\n", envp[0]);
// 	// printf("%s\n", envp[i]);
//     envp[1] = ft_strjoin("OLDPWD=", "");  // NULL value represented as empty string
//     // printf("%s\n", envp[i]);
// 	// printf("%s\n", envp[1]);
// 	envp[2] = ft_strjoin("PWD=", pwd);
// 	// printf("%s\n", envp[i]);
// 	// printf("%s\n", envp[2]);
//     envp[3] = ft_strjoin("_=", "/usr/bin/env");
// 	// printf("%s\n", envp[i]);
// 	// printf("%s\n", envp[3]);
//     envp[4] = ft_strjoin("SHLVL=", "1");
// 	// printf("%s\n", envp[4]);
//     envp[5] = NULL;

//     free(pwd);  // Clean up the allocated memory for pwd

//     return (envp);
// }

char    **get_env(void)
{
	// printf("get this point\n");
    // static char    *envp[6];
    char    *pwd;
	char **envp;
    // int     i = 0;

    // Allocate space for 6 environment variables + NULL terminator
    envp = (char **)malloc(sizeof(char *) * 6);
    if (!envp)
        return (NULL);  // Handle allocation failure

    pwd = getcwd(NULL, 0);
    if (!pwd)
        return (NULL);
    // Set environment variables
	// printf("%s\n", envp[i]);
    envp[0] = ft_strjoin("PATH=", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
    envp[1] = ft_strjoin("OLDPWD=", "");  // NULL value represented as empty string
	envp[2] = ft_strjoin("PWD=", pwd);
    envp[3] = ft_strjoin("_=", "/usr/bin/env");
    envp[4] = ft_strjoin("SHLVL=", "1");
    envp[5] = NULL;

    free(pwd);  // Clean up the allocated memory for pwd

    return (envp);
}

char	**set_env(char **env)
{
	int		i;
	int		num_strings;
	char	**envp;

	// if(!env || !env[0])
	// 	envp = get_env();
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
