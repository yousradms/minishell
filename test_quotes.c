#include <libc.h>

void handle_quotes_ex(t_command **cmd)
{
    t_command *first;
    int i;
    char *cleaned_arg;
    
    first = *cmd;
    i = 0;
    cleaned_arg = NULL;
    while(first)
    {
        while(first->arg[i])
        {
            if(strchr(first->arg[i],'\''))
            {
                cleaned_arg = remove_squotes(first->arg[i]);
                free(first->arg[i]);
                first->arg[i] = cleaned_arg;
                i++;
            }
            if(strchr(first->arg[i],'\"'))
            {
                cleaned_arg = remove_dquotes(first->arg[i]);
                free(first->arg[i]);
                first->arg[i] = cleaned_arg;
                i++; 
            }
            else
                i++;
        }
        first = first->next;
    } 
}