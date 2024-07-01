#include "../minishell.h"
//-nnnnnnn->1
// Function to check if a string represents a sequence of '-n'
int check_n(char *s)
{
    // Skip any initial '-' characters
    while (*s == '-') {
        s++;
    }

    // Check if the remaining characters are all 'n'
    while (*s == 'n') {
        s++;
    }

    // Return true if we've reached the end of the string
    return (*s == '\0');
}
// Main echo function in your minishell
void ft_echo(t_command **cmd)
{
    int i = 1;
    int n_option = 0;
    // t_command *first = *cmd;
    // while(first != NULL)
    // {
    //     int l = 0;
    //     while(first->arg[l])
    //     {
    //         printf("[%d][##%s##]\n",l,first->arg[l]);
    //         l++;
    //     }
    //     first = first->next;
    // }
    //(void)cmd;
    //printf("hi");
    // Check if the second argument is "-n"
    //printf("[%s]\n",(*cmd)->arg[1]);
    if ((*cmd)->arg[1] != NULL && strcmp((*cmd)->arg[1], "-n") == 0) {
        n_option = 1;
        i++;
    }

    // // Loop through arguments and print them
    while ((*cmd)->arg[i] != NULL) {
        // Check if the argument is not a sequence of "-n"
        if (!check_n((*cmd)->arg[i])) {
            //printf("enter");
            printf("%s", (*cmd)->arg[i]);
            if ((*cmd)->arg[i + 1] != NULL) {
                printf(" ");
            }
        }
        i++;
    }

    // // Print newline if -n option was not used
    if (n_option == 0) {
        printf("\n");
    }

    fflush(stdout);
}