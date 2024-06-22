/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/22 20:24:26 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_env(char **line,char ***env)
{
    if (strcmp(*line, "env") == 0)
    {
        char **envp = *env;
        while (*envp != NULL)
        {
            printf("%s\n", *envp);
            envp++;
        }
    }
    else if (strcmp(*line, "exit") == 0)
    {
        printf("Exiting minishell\n");
        exit(0);
    }  
}

void parsing_command(char **line,char **env)
{
    char **result;
    char *new_line;
    t_command *command;
    int i;
    
    new_line = add_delimiter(*line);                                                                                                                                                                                                                                                                              
    result = ft_split(*line);
    i = 0;
    t_node *head = NULL;
    while (result[i])
    {
        tokenize(result[i], &head, get_state(result[i]));
        i++;
    }
    //print_list(head);
    parsing(&head);
    expanding(head,env);
    command = ft_split2(&head);
    //print_list2(command);
    //execute(&command);
    free(result);
    free_precedent_nodes(head);  
}

int main(int ac,char **av,char **env)
{ 
    (void)ac;
    (void)av;
    
    while(1)
    {
        char *line;
        line = readline("minishell==");
        if(!line)
            exit(1);
        set_env(&line, &env);
        if(line[0] == '\0' || just_spaces(line))
        {
            free(line);
            continue;
        }
        if(ft_strlen(line) > 0)
        {
            add_history(line);
            parsing_command(&line,env);
        }
        free(line);
    }
    return(0);
}



