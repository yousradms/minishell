/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:45:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/21 19:47:50 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void free_char_array(char **array)
{
    if (array == NULL)
        return;

    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
    free(array);
}
static void free_env_list(t_env *head)
{
    t_env *current = head;
    t_env *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->var);
        free(current->value);
        free(current);
        current = next;
    }
}


int is_builtin(char *cmd)
{
    if (cmd && strcmp(cmd, "cd") == 0)
        return (1);
    else if (cmd && strcmp(cmd, "unset") == 0)
        return (1);
    else if (cmd && strcmp(cmd, "exit") == 0)
        return (1);
    else if (cmd && strcmp(cmd, "echo") == 0)
        return (1);
    else if (cmd && strcmp(cmd, "pwd") == 0)
        return (1);
    else if (cmd && strcmp(cmd, "export") == 0)
        return (1);
    else if (cmd && strcmp(cmd, "env") == 0)
        return (1);
    else
        return (0);
}

void env_list(t_env **env, char **envp)
{
    t_env *head;
    t_env *last;
    int i;
    char *equal_sign;
    char *var;
    char *value;
    t_env *new_env;
    
    head = NULL;
    last = NULL;
    i = 0;
    while (envp[i] != NULL)
    {
        equal_sign = strchr(envp[i], '=');
        value = NULL;
        if (equal_sign != NULL)
        {
            // Allocate memory for var and value
            var = (char *)malloc((equal_sign - envp[i] + 1) * sizeof(char));
            if (!var)
                return ;
            value = (char *)malloc((strlen(equal_sign + 1) + 1) * sizeof(char));
            if (!value)
                return ;
            // Copy var and value
            strncpy(var, envp[i], equal_sign - envp[i]);
            var[equal_sign - envp[i]] = '\0'; // Null-terminate var
            strcpy(value, equal_sign + 1);
        }
        else
        {
            // No '=', treat entire string as var
            var = (char *)malloc((strlen(envp[i]) + 1) * sizeof(char));
            if (!var)
                return ;
            strcpy(var, envp[i]);
        }
        // Allocate memory for t_env structure
        new_env = (t_env *)malloc(sizeof(t_env));
        if(!new_env)
            return ;
        new_env->var = var;
        new_env->value = value;
        new_env->next = NULL;
        new_env->prev = last;
        // Update pointers
        if (head == NULL)
            head = new_env;
        if (last != NULL)
            last->next = new_env;
        last = new_env;
        i++;
    }
    // Update the pointer to the head of the list
    *env = head;
}
char  **env_to_char_array(t_env *env)
{
    int count = 0;
    t_env *current = env;

    // Count the number of elements in the linked list
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Allocate memory for the char ** array
    char **envp = (char **)malloc((count + 1) * sizeof(char *)); // +1 for NULL terminator

    // Populate the char ** array
    current = env;
    int i = 0;
    int var_len;
    int value_len ;
    while (current != NULL) {
        // Calculate the lengths of var and value
        if(current->var)
            var_len = strlen(current->var);
        if(current->value)
            value_len = strlen(current->value);

        // Allocate memory for the combined string "var=value"
        envp[i] = (char *)malloc((var_len + value_len + 2) * sizeof(char));
        
        // Copy variable name (var)
        strcpy(envp[i], current->var);
        if(current->value)
        {
        // Concatenate '='
            strcat(envp[i], "=");
        
        // Concatenate value
            strcat(envp[i], current->value);
        }

        i++;
        current = current->next;
    }

    // Set the last element of the array to NULL as required by execve and other functions
    envp[i] = NULL;
    return(envp);


}
char **execute_builtin(t_command **command, char **envp)
{
    t_env *env = NULL; // Initialize linked list head for environment variables
    env_list(&env, envp);
    if (strcmp((*command)->arg[0], "echo") == 0) 
        ft_echo(command);
    
    else if (strcmp((*command)->arg[0], "cd") == 0) 
        ft_cd(command,&env);
    
    else if (strcmp((*command)->arg[0], "pwd") == 0) 
        ft_pwd(command);
    
    else if (strcmp((*command)->arg[0], "export") == 0) 
        
        ft_export(command,&env);
    
    else if (strcmp((*command)->arg[0], "unset") == 0)
    {
        // Determine number of arguments excluding the command itself
        int num_args = 0;
        while ((*command)->arg[num_args] != NULL)
            num_args++;
        // Call ft_unset with arguments starting from index 1
        if (num_args > 1)
            ft_unset(&((*command)->arg[1]), num_args - 1, &env);
         else {
            printf("Usage: unset <variable> [<variable> ...]\n");
        }
    }
    else if (strcmp((*command)->arg[0], "env") == 0) {
        
        ft_env(command, &env); // Pass the command and the linked list of environment variables
    }
    else if (strcmp((*command)->arg[0], "exit") == 0) {
        ft_exit(command);
    }
    else {
        fprintf(stderr, "Unknown built-in command\n");
    }
    char **new_envp = env_to_char_array(env);
    free_char_array(envp);
    free_env_list(env);

    return (new_envp);

}