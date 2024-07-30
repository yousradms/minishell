/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:55 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/28 20:19:40 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

static void get_expoted(t_env **envp)
{
	t_env *current;
	
	current = *envp;
	while (current != NULL)
	{
		printf("declare -x %s",current->var);
		if (current->value != NULL)
			printf("=\"%s\"\n",current->value);
		else
			printf("\n");
		current = current->next;
	}
}

static void process_argument(t_env **envp, char *arg)
{
	char *key;
	char *value;
	t_env *tmp;
	int found;
	
	key = extract_var(arg);
	value = extract_value(arg);
	tmp = *envp;
	found = 0;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->var))
		{
			found = 1;
			update_existing_env(tmp, arg, value);
			break;
		}
		tmp = tmp->next;
	}
	if (!found)
		add_new_env(envp, key, value);
	free(key);
	free(value); 
}

void ft_export(t_command **command, t_env **envp)
{
	int i;
	
	if ((*command)->arg[1] == NULL)
	{
		get_expoted(envp);
		return ;
	}
	i = 1;
	while ((*command)->arg[i] != NULL)
	{
		if (!check_arg((*command)->arg[i]))
			fprintf(stderr, "Minishell: `%s': not a valid identifier\n", (*command)->arg[i]);  
		else
			process_argument(envp, (*command)->arg[i]);
		i++;
	}
}
