#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
    struct s_env *prev;
} t_env;

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
