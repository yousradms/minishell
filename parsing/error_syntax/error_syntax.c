/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:57:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 14:31:07 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

// static void	ft_handl_error(char *s1, char *s2, char *s3)
// {

// 	char	*str;

// 	str = ft_strjoin(s1, ft_strjoin(s2, s3));
// 	ft_putendl_fd(str, 2);
// }

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
		return;
	str = temp2;
	ft_putendl_fd(str, 2);
	free(str);
}

static int	error_pipe(t_node *token)
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
                return (open_here(token, tmp), ft_handl_error(NAME, "", ERR_PIPE), -1);
        }
        last_pipe = tmp->type;
        tmp = tmp->next; // Move to the next tmp
        if (!tmp)
        {
            if (last_pipe == 2)
                return (open_here(token, tmp), ft_handl_error(NAME, "", ERR_PIPE), -1);
        }
    }
    return (1);
}

static int	error_red(t_node *token)
{
    t_node  *tmp;
    
    tmp = token;
	while (tmp)
	{
		if ((tmp->type == 3 || tmp->type == 4 || tmp->type == 5 || tmp->type == 6) && tmp->next == NULL)
			return (open_here(token, tmp), ft_handl_error(NAME, ERR_FILE, tmp->content), -1);
		if ((tmp->type == 3 || tmp->type == 4 || tmp->type == 5|| tmp->type == 6) && tmp->next != NULL)
		{
			tmp = tmp->next;
			while (tmp->type == 1 && tmp->next != NULL)
				tmp = tmp->next;
			if (tmp->type != 9 )//&& tmp->type != SIGN && tmp->type != EXIT_STATUS)
				return (open_here(token, tmp), ft_handl_error(NAME, ERR_FILE, tmp->content), -1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int parsing(t_node *head)
{
    if (error_pipe(head) == -1)
        return (-1);
    if (error_red(head) == -1)
        return (-1);
    return (1);
}