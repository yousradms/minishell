/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/03 14:53:28 by ydoumas          ###   ########.fr       */
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
    new_line = add_delimiter(*line);//problem here
    //printf("line is : %s\n",new_line);
    char *s = ft_strtrim(new_line," ");                                                                                                                                                                                                                                                                            
    result = ft_split(s);
    //print_darg(result);
    i = 0;
    t_node *head = NULL;
    while (result[i])//tokenize
    {
        tokenize(result[i], &head, get_state(result[i]));
        i++;
    }
    //print_list(head);
    expanding(head, env);
    if (parsing(head) == -1)
	{
		free_precedent_nodes(head);
		return ;
	}
    t_command *commands = ft_split2(&head);//splut pipe-->t_command
    //print_list2(commands);
    handle_herddoce(&commands);
    handle_multiple_command(&commands,env);//execution
    free_commands(commands);
    free(result);
    free_precedent_nodes(head);
    free(s); 
}
int handle_herdoc(char *delimiter, int f) 
{
    char *line;
    int temp_fd;

    // Open or create "temp.txt" for appending
    if (f)
    {
        temp_fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (temp_fd == -1) {
            perror("Error creating temporary file");
            exit(0);
        }
    }

    while (1) {
        line = readline("heredoc> ");
        if (line == NULL)
            break;

        // Check for the delimiter at the start of the line
        if (strncmp(line, delimiter, strlen(delimiter)) == 0 && line[strlen(delimiter)] == '\0') {
            free(line);
            break; // Exit loop when delimiter is found
        }

        // Write the line and newline character to the temporary file
        if (f)
        {
            if (write(temp_fd, line, strlen(line)) == -1) {
                perror("Error writing to temporary file");
                free(line);
                close(temp_fd);
                exit(0);
            }
            if (write(temp_fd, "\n", 1) == -1) {
                perror("Error writing to temporary file");
                free(line);
                close(temp_fd);
                exit(0);
            }
        }
        free(line);
    }

    // Close the temporary file after writing
    if (f)
    {
        close(temp_fd);
        temp_fd = open("temp.txt", O_RDONLY, 0644);
        if (temp_fd == -1) {
            perror("Error opening temporary file for reading");
            exit(0);
        }
        int my_fd = temp_fd;
        close(temp_fd);
        if (unlink("temp.txt") == -1) {
            perror("Error removing temporary file");
            exit(0);
        }
        return(my_fd);
    }
    return (0);
}
void handle_herddoce(t_command **command)
{
    t_command *first = *command;
    while(first != NULL)
    {
        int i = 0;
        while(first->arg[i])
        {
            if(strcmp(first->arg[i],"<<") == 0)
            {
                //printf("#%s#\n",first->arg[i + 1]);
                if(first->arg[i + 1])
                    first->my_fd = handle_herdoc(first->arg[i + 1], 1);
                    
            }
            i++;
        } 
        first = first->next;
    }
}
// static int erroor_pipe(t_command **command) {
//     t_command *curr = *command;

//     while (curr) {
//         int i = 0;
//         while (curr->arg[i]) {
//             if (strcmp(curr->arg[i], "|") == 0) {
//                 if (curr->arg[i + 1] == NULL) {
//                     printf("minishell: syntax error near unexpected token `|'\n");
//                     return -1;
//                 }
//             }
//             i++;
//         }
//         curr = curr->next;
//     }

//     return 1;
// }
// int handle_herdoc(char *delimiter) 
// {
//     char *line;
//     int temp_fd;
    

//     // Open or create "temp.txt" for appending
//     temp_fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
//     if (temp_fd == -1) {
//         perror("Error creating temporary file");
//         exit(0);
//     }

//     while (1) {
//         line = readline("heredoc> ");
//         if (line == NULL)
//             break;

//         // Check for the delimiter at the start of the line
//         if (strncmp(line, delimiter, strlen(delimiter)) == 0 && line[strlen(delimiter)] == '\0') {
//             free(line);
//             break; // Exit loop when delimiter is found
//         }

//         // Write the line and newline character to the temporary file
//         if (write(temp_fd, line, strlen(line)) == -1) {
//             perror("Error writing to temporary file");
//             free(line);
//             close(temp_fd);
//             exit(0);
//         }
//         if (write(temp_fd, "\n", 1) == -1) {
//             perror("Error writing to temporary file");
//             free(line);
//             close(temp_fd);
//             exit(0);
//         }

//         free(line);
//     }

//     // Close the temporary file after writing
//     close(temp_fd);
//     temp_fd = open("temp.txt", O_RDONLY, 0644);
//     if (temp_fd == -1) {
//         perror("Error opening temporary file for reading");
//         exit(0);
//     }
//     int my_fd = temp_fd;
//     close(temp_fd);
//     if (unlink("temp.txt") == -1) {
//         perror("Error removing temporary file");
//         exit(0);
//     }
//     return(my_fd);
// }
// void handle_herddoce(t_command **command) {
//     t_command *first = *command;
//     while (first != NULL) {
//         int i = 0;
//         while (first->arg[i]) {
//             if (strcmp(first->arg[i], "<<") == 0) {
//                 if (first->arg[i + 1]) {
//                     first->my_fd = handle_herdoc(first->arg[i + 1]);
//                     if (first->my_fd == -1) {
//                         if (erroor_pipe(command) == -1 ) {
//                             printf("minishell: syntax error near unexpected token `%s'\n", first->arg[i + 1]);
//                         }
//                         else {
//                             printf("Error: Syntax error near unexpected token '%s'\n", first->arg[i + 1]);
//                         }
//                         return;
//                     }
//                 }
//             }
//             i++;
//         }
//         first = first->next;
//     }
// }




int main(int ac,char **av,char **env)
{ 
    (void)ac;
    (void)av;
    char **envp;
    char *line;
    
    envp = set_env(env);//allocate + copy
    while(1)
    {
        line = readline("minishell🥶😁");
        if(!line)
            exit(1);
        if(line[0] == '\0' || just_spaces(line))
        {
            free(line);
            continue;
        }
        if(strlen(line) > 0)
        {
            add_history(line);
            parsing_execute_command(&line,envp);
        }
        free(line);
    }
    return(0);
}



