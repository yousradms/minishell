#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

int ft_is_number(char *s)
{
    while(*s)
    {
        if(!(*s >= '0' && *s <= '9'))
            return(0);
        s++;
    }
    return(1);
}

void ft_exit(t_command **command)
{
    int exit_status;

    if (!((*command)->arg[1]))//no arguments
    {
        printf("exit\n");
        exit(0);
    }
    else if ((*command)->arg[1])
    {
        if (!ft_is_number((*command)->arg[1]))
        {
            printf("exit: numeric argument required\n");
            exit(1);
        }
        else
        {
            exit_status = atoi((*command)->arg[1]);
            if ((*command)->arg[2])
            {
                printf("exit: too many o\n");
                exit(1);
            }
            else
            {
                printf("exit \n");
                exit(exit_status);
            }
        }
    }
}
