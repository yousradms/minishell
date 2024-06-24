#include "minishell.h"

void handle_herddoc(t_node *temp,t_node *nexte)
{
    (void)temp;
    
    while (1)
    {
        char *line;
        char *del = nexte->content;//in the cases we need to remove quotes in other cases we don't need to do that
        line = readline(">");
        //printf("##%s#",del);
        if (line == NULL || strcmp(line, del) == 0)
            break ;
    }
}