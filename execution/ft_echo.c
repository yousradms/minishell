#include "../minishell.h"
//-nnnnnnn->1
// Function to check if a string represents a sequence of '-n'
int check_n(char *s) {
    // Skip any initial '-' characters
    if (*s == '-') {
        s++;
    }
    if(*s == '\0' || *s != 'n')
        return(0);
    // Check if the remaining characters are all 'n'
    while (*s && *s == 'n') {
        s++;
    }
    // Return true if we've reached the end of the string
    return (*s == '\0');
}
// Main echo function in your minishell
void ft_echo(t_command **cmd) {
    int i = 1;
    int n_option = 0;

    while ((*cmd)->arg[i] != NULL && check_n((*cmd)->arg[i]))
    {
        n_option++;
        i++;
    }
    while ((*cmd)->arg[i] != NULL) {
        printf("%s", (*cmd)->arg[i]);
        if ((*cmd)->arg[i + 1] != NULL) {
            printf(" ");
        }
        i++;
    }
    if (!n_option)
        printf("\n");
    // You better use write instead of printf :)
}