/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:21:42 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/28 17:59:34 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

static char *prepare_line(char **line)
{
    char *new_line;
    char *s;
    
    new_line = add_delimiter(*line);
    if(!new_line)
        return(NULL);
    s = ft_strtrim(new_line, " ");
    if(!s)
        return(NULL);
    free(new_line);
    return (s);
}

static void tokenize_line(t_node **head, char **result)
{
    int i;
    
    i = 0;
    while(result[i])
    {
        tokenize(result[i], head, get_state(result[i]));
        i++;
    }
}

static void free_resources(char **result, t_node *head, char *s)
{
    free(result);
    free_precedent_nodes(head);
    free(s);
}
void export_expand(t_node **head)
{
    t_node *current = *head;
    //char *temp;
    while(current != NULL)
    {
    //     if (current->prev && current->prev->type == WORD)
    //     {
    //         while(current->prev && current->prev->type == 1)
    //             current = current->prev;
    //     if(current->prev && !ft_strncmp(current->prev->content,"export",ft_strlen("export")) && contain_env(current->prev->content))
    //     {
    //         // current->content = ft_strjoin("\"", current->content);
    //         // current->content = ft_strjoin(current->content, "\""); 
    //         temp = ft_strjoin("\"", current->content);
    //         free(current->content); // Libérer l'ancien contenu pour éviter les fuites de mémoire
    //         current->content = ft_strjoin(temp, "\"");
    //         free(temp); // Libérer le contenu temporaire  
    //     }
    // }
        if(current->content && contain_env(current->content) && current->state == 1)
        {
            
            // if (current->prev && current->prev->type == 9)
            // {
            //     current->content = ft_strjoin("\"", current->content);
            //     current->content = ft_strjoin(current->content, "\""); 
            // }
            if (current->prev && current->prev->type == 9)
            {
                while(current && current->prev && current->prev->type == 1)
                    current = current->prev;
                if (current)
                {
                    //printf("current is :[%s]\n",current->content);
                    current->content = ft_strjoin("\"", current->content);
                    current->content = ft_strjoin(current->content, "\"");
                }
            }
            
        }
        current = current->next;
    }
}
char **parsing_execute_command(char **line,char **env)
{
    
    char **result;
    char *s;
    t_node *head;
    t_command *commands;

    if (!check_quot(*line,'\'', '\"'))
	{
		write(2, "UNCLOSED QUOT\n", 14);
		return (env);
	}
    s = prepare_line(line);
    //printf("line is[%s]\n",s); 
    if(!s)
        return(env);                                                                                                                                                                                                                                                                         
    result = ft_split(s);
    //print_darg(result);
    if (!result)
    {
        free(s);
        return (env);
    }
    head = NULL;
    tokenize_line(&head, result);
    if (parsing(head) == -1)
	{
        free_resources(result, head, s);
		return (env);
	}
    
    export_expand(&head);
    // print_list(head);
    // exit(1);
    expanding(head, env);

    commands = ft_split2(&head);
    // print_list2(commands);
    handle_herddoce(&commands,env);
    env = execute(&commands,env);//leaks in the execution
    
    free_commands(commands);
    free_resources(result, head, s);
    return(env);
}

