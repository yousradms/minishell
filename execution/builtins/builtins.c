/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:45:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/05 17:44:36 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "unset") == 0 \
	|| ft_strcmp(cmd, "exit") == 0 \
	|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0 \
	|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "env") == 0))
		return (1);
	return (0);
}

static void	execute_commandb(t_command **command, t_env **env)
{
	int	num_args;

	if (ft_strcmp((*command)->arg[0], "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp((*command)->arg[0], "cd") == 0)
		ft_cd(command, env);
	else if (ft_strcmp((*command)->arg[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp((*command)->arg[0], "export") == 0)
		ft_export(command, env);
	else if (ft_strcmp((*command)->arg[0], "unset") == 0)
	{
		num_args = 0;
		while ((*command)->arg[num_args] != NULL)
			num_args++;
		if (num_args > 1)
			ft_unset(&((*command)->arg[1]), num_args - 1, env);
	}
	else if (ft_strcmp((*command)->arg[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp((*command)->arg[0], "exit") == 0)
		ft_exit(command);
}

char	**execute_builtin(t_command **command, char **envp)
{
	t_env	*env;
	char	**new_envp;

	env = NULL;
	env_list(&env, envp);
	execute_commandb(command, &env);
	new_envp = env_to_char_array(env);
	free_char_array(envp);
	free_env_list(env);
	return (new_envp);
}
