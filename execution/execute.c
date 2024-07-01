#include "../minishell.h"

int count_nbr_command(t_command *command)
{
    t_command *first = command;
    int count = 0;
    while(first != NULL)
    {
        count++;
        first = first->next;

    }
    return(count);

}

void print_command(t_command **commande)
{
        t_command *cmd = *commande;
        while(cmd != NULL)
        {
            int i = 0;
            while(cmd->arg[i])
            {
                printf("%s\n",cmd->arg[i]);
                i++;
            }
            cmd = cmd->next;
        }
}
// void execute(t_command **commande,char **env)
// {

//     handle_multiple_command(commande,env);

// }