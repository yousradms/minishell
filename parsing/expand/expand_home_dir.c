/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:17:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/08/10 19:09:56 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	expand_home_directory(t_node *current)
{
	char	*new_content;
	char	*home;

	if (!current || !current->content)
		return ;
	new_content = NULL;
	home = getenv("HOME");
	if (!home)
		return ;
	if (current->content[0] == '~')
	{
		if (current->content[1] == '\0')
			new_content = ft_strdup(home);
		else if (current->content[1] == '/')
			new_content = ft_strjoin(home, current->content + 1);
	}
	if (new_content)
	{
		free(current->content);
		current->content = new_content;
	}
}

int	contain_home1(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] && s[i] == '~' && s[i + 1] && s[i + 1] == '/')
		return (1);
	return (0);
}
