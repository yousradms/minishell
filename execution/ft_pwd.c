#include "../minishell.h"

void ft_pwd(t_command **command)
{
    (void)command;

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("pwd");
    }
}