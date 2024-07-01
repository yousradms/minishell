#include "../minishell.h"

void ft_env(t_command **command, t_env **envp) {
    (void)command; // Suppress unused parameter warning

    t_env *env = *envp; // Dereference envp to get the linked list head

    if (env == NULL) {
        fprintf(stderr, "Error: Environment poimaknter is NULL.\n");
        return;
    }

    // Iterate through the linked list of environment variables
    while (env != NULL) {
        printf("%s=%s\n", env->var, env->value);
        env = env->next; // Move to the next node
    }
}

// void	ft_env(t_env **envex)
// {
// 	t_env	*env;
// 	int		a;

// 	env = *envex;
// 	if (env == NULL)
// 	{
// 		(exit_status(127), er_print("env", ": No such file or directory\n", 1));
// 		return ;
// 	}
// 	a = env->empty;
// 	while (env)
// 	{
// 		if (env->q == 1 && env->vari != NULL && env->value != NULL)
// 		{
// 			if (a == 0)
// 				printf("%s=%s\n", env->vari, env->value);
// 			else
// 			{
// 				if (ft_strncmp("PATH", env->vari, ft_strlen(env->vari)) != 0)
// 					printf("%s=%s\n", env->vari, env->value);
// 			}
// 		}
// 		env = env->next;
// 	}
// }
