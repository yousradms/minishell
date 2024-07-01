#include "../minishell.h"

void ft_env(t_command **command, t_env **envp)
{
	(void)command; // Suppress unused parameter warning

	t_env *env = *envp; // Dereference envp to get the linked list head

	if (env == NULL) {
		// fprintf(stderr, "Error: Environment poimaknter is NULL.\n");
		return;
	}

	// Iterate through the linked list of environment variables
	while (env != NULL) {
		printf("%s=%s\n", env->var, env->value);
		env = env->next; // Move to the next node
	}
}
// char **allocate_and_copy(char **env)
// {
//     int num_strings = 0;
//     while (env[num_strings] != NULL) {
//         num_strings++;
//     }

//     char **envp = (char **)malloc(sizeof(char *) * (num_strings + 1));
//     if (envp == NULL) {
//         return NULL;
//     }

//     for (int i = 0; i < num_strings; i++)
//     {
//         envp[i] = strdup(env[i]);
//         if (envp[i] == NULL) 
//         {
//             for (int j = 0; j < i; j++)
//             {
//                 free(envp[j]);
//             }
//             free(envp);
//             return NULL;
//         }
//     }

//     envp[num_strings] = NULL; // Terminer le tableau avec un pointeur NULL
//     return envp;
// }

// char **set_env(char **env)
// {
//     int num_strings = 0;
//     while (env[num_strings] != NULL)
//         num_strings++;

//     char **envp = (char **)malloc(sizeof(char *) * (num_strings + 1));
//     if (envp == NULL)
//         return NULL;
//     while(i < num_strings)
//     {
//         envp[i] = strdup(env[i]);
//         i++;
//     }
//     envp[num_strings] = NULL;
//     return envp;
// }
