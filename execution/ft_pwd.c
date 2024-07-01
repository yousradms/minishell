#include "../minishell.h"

// void ft_pwd(t_command **command) {
//     (void)command; 

//     char cwd[4096]; 
    
//     if (getcwd(cwd, sizeof(cwd)) != NULL) {
//         printf("%s\n", cwd); 
//     } else {
//         perror("getcwd() error");
//     }
// }
void set_ennv(t_env **envp, const char *var, const char *value) {
    t_env *current = *envp;
    while (current != NULL) {
        if (strcmp(current->var, var) == 0) {
            // Variable already exists, update its value
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }

    // Variable does not exist, add it to the list
    t_env *new_env = malloc(sizeof(t_env));
    if (new_env == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE); // Handle error as needed
    }
    new_env->var = strdup(var);
    new_env->value = strdup(value);
    new_env->next = NULL;

    // Insert at the head of the list
    new_env->next = *envp;
    *envp = new_env;
}
void ft_pwd(t_command **command, t_env **envp) {
    (void)command; // Suppress unused parameter warning

    char cwd[4096]; 
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);

        // Update PWD and OLDPWD in the environment
        set_ennv(envp, "OLDPWD", getenv("PWD")); // Save current PWD as OLDPWD
        set_ennv(envp, "PWD", cwd); // Update PWD to the new current directory
    } else {
        perror("getcwd() error");
    }
}