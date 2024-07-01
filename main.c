/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/30 20:34:18 by ksellami         ###   ########.fr       */
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
static char	*extrat_word(int debut, int fin, char *newstr, char *s1)
{
	int	k;

	if (debut > fin)
	{
		newstr = (char *)malloc(1);
		if (newstr == NULL)
			return (NULL);
		newstr[0] = '\0';
		return (newstr);
	}
	newstr = (char *)malloc(sizeof(char) * (fin - debut + 2));
	if (newstr == NULL)
		return (NULL);
	k = 0;
	while (debut <= fin)
		newstr[k++] = s1[debut++];
	newstr[k] = '\0';
	return (newstr);
}

static char	*ft_strtrim(char  *s1, char  *set)
{
	int		debut;
	int		fin;
	char	*newstr;

	newstr = NULL;
	if (s1 == NULL || set == NULL)
		return (NULL);
	debut = 0;
	fin = strlen(s1) - 1;
	while (s1[debut] != '\0' && strchr(set, s1[debut]))
		debut++;
	while (fin >= 0 && strchr(set, s1[fin]))
		fin--;
	return (extrat_word(debut, fin, newstr, s1));
}

void parsing_execute_command(char **line,char **env)
{
    
    (void)env;
    char **result;
    char *new_line;
    int i;
    if (!check_quot(*line,'\'', '\"'))
	{
		write(2, "UNCLOSED QUOT\n", 14);
		return ;
	}
    new_line = add_delimiter(*line);
    //printf("line is : %s\n",new_line);
    char *s = ft_strtrim(new_line," ");                                                                                                                                                                                                                                                                            
    result = ft_split(s);
    //print_darg(result);
    i = 0;
    t_node *head = NULL;
    while (result[i])
    {
        tokenize(result[i], &head, get_state(result[i]));
        i++;
    }
    //print_list(head);
    //parsing(&head);
    
    expanding(head, env);
    //handle_herdoc(head);
    if (parsing(head) == -1)
	{

		free_precedent_nodes(head);
		return ;
	}
    t_command *commands = ft_split2(&head);
    //print_list2(commands);
    handle_multiple_command(&commands,env);
    free_commands(commands);
    free(result);
    free_precedent_nodes(head);
    free(s); 
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



