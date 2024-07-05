/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:21:42 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/05 20:32:21 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *prepare_line(char **line)
{
    char *new_line;
    char *s;
    
    new_line = add_delimiter(*line);
    s = ft_strtrim(new_line, " ");
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

void parsing_execute_command(char **line,char **env)
{
    (void)env;
    char **result;
    char *s;
    t_node *head;
    t_command *commands;

    if (!check_quot(*line,'\'', '\"'))
	{
		write(2, "UNCLOSED QUOT\n", 14);
		return ;
	}
    s = prepare_line(line);
    //printf("line is[%s]\n",s);                                                                                                                                                                                                                                                                          
    result = ft_split(s);
    //print_darg(result);
    head = NULL;
    tokenize_line(&head, result);
    if (parsing(head) == -1)//leaks here
	{
        free_resources(result, head, s);
		return ;
	}
    //print_list(head);
    expanding(head, env);
    commands = ft_split2(&head);
    //print_list2(commands);
    handle_herddoce(&commands);
    //execute(&commands,env);//--> exit work we divide into one command and multiple command but problem in expanding seg fault
    handle_multiple_command(&commands,env);
    free_commands(commands);
    free_resources(result, head, s);
}

