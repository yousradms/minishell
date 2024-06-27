
#include "../minishell.h"

void tokenize(char *s,t_node **head,t_state state)
{
    
    if (strcmp(s, " ") == 0) 
        add_node(head, create_node(s, WSPACE,state));
    else if (strcmp(s, "|") == 0) 
        add_node(head, create_node(s, PIPE,state));
    else if (strcmp(s, "<") == 0) 
        add_node(head, create_node(s, REDIN,state));
    else if (strcmp(s, ">") == 0) 
        add_node(head, create_node(s, REDOUT,state));
    else if (strcmp(s, ">>") == 0) 
        add_node(head, create_node(s, APPEND,state));
    else if (strcmp(s, "<<") == 0) 
        add_node(head, create_node(s, HEREDOC,state));
    else if (strcmp(s, "$") == 0) 
        add_node(head, create_node(s, SIGN,state));
    else if (strcmp(s, "$?") == 0) 
        add_node(head, create_node(s, EXIT_STATUS,state));
    else if (strcmp(s, "\"") == 0) 
        add_node(head, create_node(s, DQUOTE,state));
    else if (strcmp(s, "\'") == 0)
    {
        add_node(head, create_node(s, SQUOTE,state));
    }
        
    else if (s && *s) 
        add_node(head, create_node(s, WORD,state));
    else
    {
        printf("ERROR\n");
        free_precedent_nodes(*head);
        exit(1);
    }
}