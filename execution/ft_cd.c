
#include "../minishell.h"

void ft_cd(t_command **command)
{

        if ((*command)->arg[1] != NULL)
        {
            if(strcmp((*command)->arg[1], "~") == 0)
            {
                if (chdir(getenv("HOME")) == -1)
                {
                    perror("cd");
                    return;
                }

            }
            else if(strcmp((*command)->arg[1], "-") == 0)
            {
                if (chdir(getenv("OLDPWD")) == -1)
                {
                    perror("cd");
                    return;
                }   
            }
            else
            {
                //printf("##enter here3##\n");
                if (chdir((*command)->arg[1]) == -1)
                {
                    perror("cd");
                    return;
                } 
            }

        }
        else
        {
            //printf("enter here2\n");
            if (chdir(getenv("HOME")) == -1)
            {
                perror("cd");
                return;
            }
        }
    }