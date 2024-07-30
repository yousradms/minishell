/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:57:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/28 20:28:51 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//done
#include "../../minishell.h"
#include "../../libft/libft.h"

static void	ft_handl_error(char *s1, char *s2, char *s3)
{
	char *temp1;
	char *temp2;
	char *str;

	temp1 = ft_strjoin(s1, s2);
	if (!temp1)
		return;
	temp2 = ft_strjoin(temp1, s3);
	free(temp1);
	if (!temp2)
		return ;
	str = temp2;
	ft_putendl_fd(str, 2);
	free(str);
}

static int error_pipe(t_node *token,char **env)
{
	int	last_pipe;
	t_node  *tmp;
	
	tmp = token;
	if (tmp && tmp->type == 2)
		return (ft_handl_error(NAME, "", ERR_PIPE), -1);
	while (tmp)
	{
		if (tmp->type == 2 && tmp->next != NULL)
		{
			tmp = tmp->next;
			while (tmp->type == 1 && tmp->next != NULL)
				tmp = tmp->next;
			if (tmp->type == 2)
				return (open_here(token, tmp, env), ft_handl_error(NAME, "", ERR_PIPE), -1);
		}
		last_pipe = tmp->type;
		tmp = tmp->next;
		if (!tmp)
		{
			if (last_pipe == 2)
				return (open_here(token, tmp, env), ft_handl_error(NAME, "", ERR_PIPE), -1);
		}
	}
	return (1);
}

static int	error_red(t_node *token, char **env)
{
	t_node  *tmp;
	
	tmp = token;
	while (tmp)
	{
		if ((tmp->type == 3 || tmp->type == 4 || tmp->type == 5 || tmp->type == 6) && tmp->next == NULL)
			return (open_here(token, tmp, env), ft_handl_error(NAME, ERR_FILE, tmp->content), -1);
		if ((tmp->type == 3 || tmp->type == 4 || tmp->type == 5|| tmp->type == 6) && tmp->next != NULL)
		{
			tmp = tmp->next;
			while (tmp->type == 1 && tmp->next != NULL)
				tmp = tmp->next;
			if (tmp->type != 9 )//&& tmp->type != SIGN && tmp->type != EXIT_STATUS)
				return (open_here(token, tmp, env), ft_handl_error(NAME, ERR_FILE, tmp->content), -1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int parsing(t_node *head,char **env)
{
	if (error_pipe(head,env) == -1)
		return (-1);
	if (error_red(head,env) == -1)
		return (-1);
	return (1);
}
