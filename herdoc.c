#include "minishell.h"

void handle_herddoc(t_node *temp,t_node *nexte)
{
    (void)temp;
    
    while (1)
    {
        char *line;
        char *del = remove_quotes(nexte->content);
        line = readline(">");
        //printf("##%s#",del);
        if (line == NULL || strcmp(line, del) == 0)
            break ;
    }
}