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

//Function to execute built-in commands

void execute_builtin(t_command **command)
{
    if (strcmp((*command)->arg[0], "echo") == 0)
    {
        ft_echo(command);
    }
    else if (strcmp((*command)->arg[0], "cd") == 0)
    {   
        ft_cd(command);
    }       
    else if(strcmp((*command)->arg[0], "pwd") == 0)
        ft_pwd(command);
    else if (strcmp((*command)->arg[0], "export") == 0)
        ft_export(command);
    else if (strcmp((*command)->arg[0], "unset") == 0)
        ft_unset(command);
    else if (strcmp((*command)->arg[0], "env") == 0)
        ft_env(command);
    else if (strcmp((*command)->arg[0], "exit") == 0)
        ft_exit(command);
    else
    {
        fprintf(stderr, "Unknown built-in command\n");
    }
}