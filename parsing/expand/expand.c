/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/14 14:13:45 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

static void	handle_heredoc_expand(t_node **current, int *in_herdoc)
{
	if ((*current)->type == 6)
	{
		*in_herdoc = 1;
		while ((*current)->next && (*current)->next->type == 1)
			*current = (*current)->next;
	}
}

// static void	remove_dollor_quotes(t_node **list)
// {
// 	t_node	*current;

// 	if (!list || !*list)
// 		return ;
// 	current = *list;
// 	while (current != NULL && current->next != NULL)
// 	{
// 		if (ft_strcmp(current->content, "$") == 0 \
// 		&& current->next && current->next->content[0] \
// 		&& (current->next->content[0] == '\"' \
// 		|| current->next->content[0] == '\'') && current->state == GENERAL \
// 		&& (current->next->state == DQ || current->next->state == SQ))
// 			current->content = ft_strdup("");
// 		else
// 			current = current->next;
// 	}
// }

// static void remove_dollor_quotes(t_node **list)
// {
//     // print_list(*list);
//     t_node *current = *list;
//     while (current) // Check for NULL at each iteration
//     {
//         if (current->type == 7)
//         {
// 			if(!current->next)
// 				break;
//             // printf("Enter here\n");
// 			// printf("the current content=====>>%s\n",current->content);
// 			current->content = ft_strdup("");
//             // Perform the necessary operations here, like modifying the node
//             // If you remove the node, you need to update the list pointer
//             // and the current pointer accordingly
//         }
//         // Move to the next node
//         current = current->next;
//     }
// }

// static void remove_dollor_quotes(t_node **list)
// {
//     // print_list(*list);
//     t_node *current = *list;
//     while (current) // Check for NULL at each iteration
//     {
//         if (current->type == 7)
//         {
// 			if(!current->next || current->next->type == 7)
// 				break;
//             // printf("Enter here\n");
// 			// printf("the current content=====>>%s\n",current->content);
// 			if (current->next && (current->next->content[0] = '\"' || current->next->content[0] == '\"'))
// 				current->content = ft_strdup("");
//             // Perform the necessary operations here, like modifying the node
//             // If you remove the node, you need to update the list pointer
//             // and the current pointer accordingly
//         }
//         // Move to the next node
//         current = current->next;
//     }
// }
static void remove_dollor_quotes(t_node **list)
{
    t_node *current = *list;
    t_node *next_node;

    while (current) // Check for NULL at each iteration
    {
        if (current->type == 7)
        {
            if (!current->next || current->next->type == 7)
                break;

            // Check if the next node's content starts and ends with quotes
            if (current->next && current->next->content[0] == '\"')
            {
                // Free the old content and set it to an empty string
                free(current->content);
                current->content = ft_strdup("");

                // Ensure ft_strdup returns a non-null pointer
                if (!current->content)
                {
                    // Handle memory allocation failure (optional)
                    return; // or handle error as needed
                }

                // Optional: Remove the next node if needed and adjust the list
                next_node = current->next;
                current->next = next_node->next;
                free(next_node->content);
                free(next_node);
            }
        }
        // Move to the next node
        current = current->next;
    }
}


t_node	*process_current_node(t_node *current, char **env, int *in_herdoc)
{
	while (current && current->type == 1)
		current = current->next;
	if (current == NULL)
		return (NULL);
	if (*in_herdoc && current->next)
		current = current->next;
	if (current->type == 9 && contain_env(current->content) && *in_herdoc != 1)
		expand_variable(current, env);
	else if (current->type == 9 && contain_home_after_quote(current->content) \
		&& *in_herdoc != 1 && (current->next == NULL \
		|| current->next->type == 1))
		expand_home_directory(current);
	else if (current->type == 9 && \
	contain_home1(current->content) && !(*in_herdoc))
		expand_home_directory(current);
	return (current);
}

void	set_expanded(char **str, char **content, char **env)
{
	char	*expanded;
	int		i;
	int		j;

	if (!str || !*str || !content || !env)
		return ;
	expanded = ft_strdup(*str);
	if (!expanded)
		return ;
	i = 0;
	while (expanded[i])
	{
		if (expanded[i] == '$')
		{
			j = i + 1;
			handle_special_cases(&expanded, &i, &j, env);
			if (ft_strchr(expanded, '$') == NULL \
			|| ft_strcmp(expanded, "") == 0)
				break ;
		}
		else
			i++;
	}
	free(*content);
	*content = expanded;
}

void	expanding(t_node *list, char **env)
{
	t_node	*current;
	int		in_herdoc;

	if (!list)
		return ;
	// printf("====>>[%s]\n", list->content);
	// exit(1);
	remove_dollor_quotes(&list);
	// "$USER$"

	in_herdoc = 0;
	current = list;
	while (current != NULL)
	{
		handle_heredoc_expand(&current, &in_herdoc);
		if (current == NULL)
			break ;
		current = process_current_node(current, env, &in_herdoc);
		if (current != NULL)
			current = current->next;
		in_herdoc = 0;
	}
}
