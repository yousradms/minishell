/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 12:45:07 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	get_expoted(t_env **envp)
{
	t_env	*current;

	current = *envp;
	while (current != NULL)
	{
		printf("declare -x %s", current->var);
		if (current->value != NULL)
			printf("=\"%s\"\n", current->value);
		else
			printf("\n");
		current = current->next;
	}
}

static char	*get_value_from_arg(char *arg)
{
	char	*value;

	if (ft_strchr(arg, '=') != NULL)
	{
		value = extract_value(arg);
		if (!value)
			value = ft_strdup("");
	}
	else
		value = NULL;
	return (value);
}

static void	process_argument(t_env **envp, char *arg)
{
	char	*key;
	char	*value;
	t_env	*tmp;
	int		found;

	key = extract_var(arg);
	// if (ft_strchr(arg, '=') != NULL)
	// {
	// 	value = extract_value(arg);
	// 	if (!value)
	// 		value = ft_strdup("");
	// }
	// else
	// 	value = NULL;
	value = get_value_from_arg(arg);
	tmp = *envp;
	found = 0;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->var))
		{
			found = 1;
			update_existing_env(tmp, arg, value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		add_new_env(envp, key, value);
	free(key);
	free(value);
}

int	validate_argument(char *arg)
{
	if (!check_arg(arg))
	{
		write(2, "Minishell: `", 12);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 27);
		return (0);
	}
	return (1);
}


void	ft_export(t_command **command, t_env **envp)
{
	int		i;
	int		status;
	char	*ex;

	if ((*command)->arg[1] == NULL)
	{
		get_expoted(envp);
		ex = exit_s(1, 0);
		free(ex);
		return ;
	}
	i = 1;
	status = 0;
	while ((*command)->arg[i] != NULL)
	{
		if (!validate_argument((*command)->arg[i]))
			status = 1;
		else
			process_argument(envp, (*command)->arg[i]);
		i++;
	}
	ex = exit_s(status, 1);
	free(ex);
}
