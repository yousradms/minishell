#include "../minishell.h"

void ft_pwd(t_command **command) {
    (void)command; 

    char cwd[4096]; 
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd); 
    } else {
        perror("getcwd() error");
    }
}