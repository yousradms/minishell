
#include "../minishell.h"

char **set_env(char **env)
{
    int i =0;
    int num_strings = 0;
    while (env[num_strings] != NULL)
        num_strings++;

    char **envp = (char **)malloc(sizeof(char *) * (num_strings + 1));
    if (envp == NULL)
        return NULL;
    while(i < num_strings)
    {
        envp[i] = strdup(env[i]);
        i++;
    }
    envp[num_strings] = NULL;
    return envp;
}