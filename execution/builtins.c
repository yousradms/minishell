#include "../minishell.h"
// Function to check if the command is a built-in command
int is_builtin(char *cmd)
{
    if (strcmp(cmd, "cd") == 0)
        return 1;
    else if (strcmp(cmd, "unset") == 0)
        return 1;
    else if (strcmp(cmd, "exit") == 0)
        return 1;
    else if (strcmp(cmd, "echo") == 0)
        return 1;
    else if (strcmp(cmd, "pwd") == 0)
        return 1;
    else if (strcmp(cmd, "export") == 0)
        return 1;
    else if (strcmp(cmd, "env") == 0)
        return 1;
    else
        return 0;
}
//Function li kat7ewel lina char **env l linked list
void env_list(t_env **env, char **envp)
{
    // Initialize pointers
    t_env *head = NULL;
    t_env *last = NULL;
    
    // Loop through envp
    for (int i = 0; envp[i] != NULL; i++)
    {
        // Split string at '='
        char *equal_sign = strchr(envp[i], '=');
        char *var;
        char *value = NULL;
        
        if (equal_sign != NULL)
        {
            // Allocate memory for var and value
            var = (char *)malloc((equal_sign - envp[i] + 1) * sizeof(char));
            value = (char *)malloc((strlen(equal_sign + 1) + 1) * sizeof(char));
            
            // Copy var and value
            strncpy(var, envp[i], equal_sign - envp[i]);
            var[equal_sign - envp[i]] = '\0'; // Null-terminate var
            
            strcpy(value, equal_sign + 1);
        }
        else
        {
            // No '=', treat entire string as var
            var = (char *)malloc((strlen(envp[i]) + 1) * sizeof(char));
            strcpy(var, envp[i]);
        }
        
        // Allocate memory for t_env structure
        t_env *new_env = (t_env *)malloc(sizeof(t_env));
        new_env->var = var;
        new_env->value = value;
        new_env->next = NULL;
        new_env->prev = last;
        
        // Update pointers
        if (head == NULL)
        {
            head = new_env;
        }
        
        if (last != NULL)
        {
            last->next = new_env;
        }
        
        last = new_env;
    }
    
    // Update the pointer to the head of the list
    *env = head;
}
//Function to execute built-in commands

void execute_builtin(t_command **command, char **envp) {
    t_env *env = NULL; // Initialize linked list head for environment variables
    env_list(&env, envp); // Populate the linked list with environment variables

    if (strcmp((*command)->arg[0], "echo") == 0) {
        ft_echo(command);
    }
    else if (strcmp((*command)->arg[0], "cd") == 0) {
        ft_cd(command);
    }
    else if (strcmp((*command)->arg[0], "pwd") == 0) {
        ft_pwd(command);
    }
    else if (strcmp((*command)->arg[0], "export") == 0) {
        ft_export(command);
    }
    else if (strcmp((*command)->arg[0], "unset") == 0) {
        ft_unset(command);
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
}