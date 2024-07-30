/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:14:03 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/25 21:06:09 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

void free_commands(t_command *commands)
{
	t_command *temp;
	int i;
	
	while (commands != NULL)
	{
		temp = commands;
		commands = commands->next;
		free(temp->cmd);
		if (temp->arg)
		{
			i = 0;
			while (temp->arg[i] != NULL)
			{
				free(temp->arg[i]);
				i++;
			}
			free(temp->arg);
		}
		free(temp);
	}
}

void free_arg(char **result)
{
	int i;

	i = 0;
	if (result)
	{
		while (result[i])
		{
			free(result[i]);
			i++;
		}
		free(result);
	}
}
