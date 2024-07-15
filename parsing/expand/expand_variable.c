/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:09:19 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/15 19:16:42 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *extract_variable_name(char *expanded, int i, int j)
{
    size_t var_length;
    char *var_name;
    
    var_length = j - i - 1;
    var_name = malloc(var_length + 1);
    strncpy(var_name, expanded + i + 1, var_length);
    var_name[var_length] = '\0';
    return var_name;
}

void replace_numeric_variable(char **expanded, int *i, int j)
{
    *expanded = replace_variable(*expanded, "", *i, j + 1);
    *i += 1;
}

void process_variable(char **expanded, int *i, int *j, char **env)
{
    int k;
    char *var_name;

    k = *j;
    while ((*expanded)[k] != '\0' && (*expanded)[k] != ' ' && (*expanded)[k] != '$' && is_valid_char((*expanded)[k]))
        k++;
    *j = k;
    var_name = extract_variable_name(*expanded, *i, *j);
    set_value(i, j, &var_name, expanded, env);
    free(var_name);
}

// static int	check_env_value(char **var, char **envp)
// {
// 	t_env	*env ;
//     env_list(env,envp);//transform char ** to linked list

// 	while (env)
// 	{
// 		if (!strcmp(*var, env->var))
// 			return (0);
// 		env = env->next;
// 	}
// 	return (1);
// }
// void set_expanded(char **str, char **content, char **env)
// {
//     char *expanded;
//     int i;
//     int j;

//     expanded = strdup(*str);
//     i = 0;
//     while (expanded[i] != '\0')
//     {
//         if (expanded[i] == '$')
//         {
//             j = i + 1;
//             if (expanded[j] == '0')
//             {
//                 // Replace the $0 with the word "Minishell"
//                 char *new_expanded;
//                 int new_len;

//                 // Calculate the new length
//                 new_len = strlen(expanded) - 2 + strlen("Minishell") + 1; // -2 to remove $0, +strlen("Minishell") to add "Minishell", +1 for null terminator
                
//                 // Allocate memory for new expanded string
//                 new_expanded = malloc(new_len);
//                 if (!new_expanded)
//                 {
//                     perror("malloc");
//                     exit(EXIT_FAILURE);
//                 }

//                 // Copy parts of the original string and insert "Minishell"
//                 strncpy(new_expanded, expanded, i); // Copy up to $ (excluding $)
//                 strcpy(new_expanded + i, "Minishell"); // Copy "Minishell" after $
//                 strcpy(new_expanded + i + strlen("Minishell"), expanded + j + 1); // Copy the rest of the string after $0

//                 // Update expanded
//                 free(expanded);
//                 expanded = new_expanded;

//                 // Move i past the inserted "Minishell"
//                 i += strlen("Minishell");
//             }
//             else if (expanded[j] >= '0' && expanded[j] <= '9' && expanded[j - 1] == '$')
//                 replace_numeric_variable(&expanded, &i, j);
//             else 
//                 process_variable(&expanded, &i, &j, env);
//         }
//         else
//             i++;
//     }
//     free(*content);
//     *content = expanded;
// }
static void handle_special_cases(char **expanded, int *i, int *j, char **env)
{
    char *new_expanded;
    char *value = NULL;

    if ((*expanded)[*i + 1] == '0')
    {
        value = strdup("Minishell");
    }
    else if ((*expanded)[*i + 1] == '*')
    {
        value = strdup("");  // For simplicity, we assume empty string for $*
    }
    else if ((*expanded)[*i + 1] == '@')
    {
        value = strdup("");  // For simplicity, we assume empty string for $@
    }
    else if ((*expanded)[*i + 1] == '#')
    {
        value = strdup("0");  // Placeholder, should be the number of positional parameters
    }

    else if ((*expanded)[*i + 1] == '!')
    {
        value = strdup("0");  // Placeholder, should be the process ID of the last background command
    }
    else
    {
        process_variable(expanded, i, j, env);
        return;
    }
    if (value)
    {
        new_expanded = replace_variable(*expanded, value, *i, *j + 1);
        free(*expanded);
        *expanded = new_expanded;
        *i += strlen(value);
        free(value);
    }
}
char	*ft_strdup(char *s1)
{
	char	*tmp;
	int		len;
	size_t	i;

	i = 0;
	len = strlen(s1);
	tmp = malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
void set_expanded(char **str, char **content, char **env)
{
    char *expanded;
    int i;
    int j;

        if (!str || !*str || !content || !env) {
        fprintf(stderr, "Invalid input: str, content, or env is NULL\n");
        return;
    }

    expanded = ft_strdup(*str);
    if(!expanded)
        return;
    i = 0;
    // if(expanded[i] == '\0')
    //     return;
    while (expanded[i] != '\0')
    {
        if (expanded[i] == '$' )
        {
            j = i + 1;
            handle_special_cases(&expanded, &i, &j, env);
            //printf("[%s]\n",expanded);
            //exit(1);
            if(strcmp(expanded,"") == 0)
                break;
        }
        else
            i++;
    }
    free(*content);
    *content = expanded;
}
// void set_expanded(char **str, char **content, char **env)
// {
//     char *expanded;
//     int i = 0;

//     // Ensure input string is not NULL
//     if (!str || !*str)
//     {
//         fprintf(stderr, "Error: Input string is NULL\n");
//         return;
//     }

//     // Duplicate the string
//     expanded = strdup(*str);
//     if (!expanded)
//     {
//         perror("strdup");
//         return;
//     }

//     // Process each character in the expanded string
//     while (expanded[i] != '\0')
//     {
//         if (expanded[i] == '$')
//         {
//             int j = i + 1;
//             if (!handle_special_cases(&expanded, &i, &j, env))
//             {
//                 free(expanded);
//                 return;
//             }
//         }
//         else
//         {
//             i++;
//         }
//     }

//     // Replace content with expanded string
//     free(*content);
//     *content = expanded;
// }


void expand_variable(t_node *current, char **env)
{
    char *str;
    char *temp;
    if(!current || !env)
        return;
    str = NULL;
    if (current->state == 2)
    {
        str = remove_dquotes(current->content);
        if(!str)
            return ;
    }
    else if (current->state == 1)
    {
        str = ft_strdup(current->content);
        if(!str)
            return ;
    }
    else if (current->state == 3)
    {
        temp = remove_squotes(current->content);
        if(!temp)
            return;
        free(current->content);
        current->content = temp;
        //printf("%s", current->content);
        return;
    }
    if(str)
    {
        set_expanded(&str, &(current->content), env);
        free(str);
    }
    //printf("%s", current->content);
}