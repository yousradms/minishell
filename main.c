/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/27 15:54:06 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quot(char *line, char a, char b)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == b)
			while (line[++i] != b)
				if (!line[i])
					return (0);
		if (line[i] == a)
		{
			while (line[++i] != a && line[i])
				;
			if (line[i] != a)
				return (0);
		}
	}
	return (1);
}
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
void free_commands(t_command *commands)
{
    t_command *temp;
    while (commands != NULL) {
        temp = commands;
        commands = commands->next;
        free(temp->cmd);
        if (temp->arg) {
            for (int i = 0; temp->arg[i] != NULL; i++) {
                free(temp->arg[i]);
            }
            free(temp->arg);
        }
        free(temp);
    }
}
void parsing_execute_command(char **line,char **env)
{
    (void)env;
    char **result;
    char *new_line;
    //t_command *command;
    int i;
    if (!check_quot(*line,'\'', '\"'))
	{
		write(2, "UNCLOSED QUOT\n", 14);
		return ;
	}
    new_line = add_delimiter(*line);
    //printf("line is : %s\n",new_line);                                                                                                                                                                                                                                                                            
    result = ft_split(*line);
    i = 0;
    t_node *head = NULL;
    while (result[i])
    {
        //printf("##after split result is %s##\n",result[i]);
        tokenize(result[i], &head, get_state(result[i]));
        i++;
    }
    //print_list(head);
    parsing(&head);
    //
    expanding(head, env);
    //handle_herdoc(head);
    //Split t_node linked list into t_command linked list
    t_command *commands = ft_split2(&head);//leaks here
    
    //Print and free the resulting t_command linked list
    // t_command *cmd = commands;
    // int l;
// t_command *cmd = commands;
// while (cmd) {
//     printf("Command: %s\n", cmd->cmd);
//     int l = 0;
//     while (cmd->arg[l]) {
//         printf("Arguments are :\n");
//         printf("%s\n", cmd->arg[l]);
//         l++;
//     }
//     cmd = cmd->next;
// }
    //print_list2(command);
    execute(&commands,env);
    //free_commands(commands);
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
        line = readline("minishell🥶😁");
        if(!line)
            exit(1);
        //set_env(&line, &env);
        if(line[0] == '\0' || just_spaces(line))
        {
            free(line);
            continue;
        }
        if(ft_strlen(line) > 0)
        {
            add_history(line);
            parsing_execute_command(&line,env);
        }
        free(line);
    }
    return(0);
}



