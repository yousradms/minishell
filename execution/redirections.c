#include "../minishell.h"

void handle_redirect_in(t_command *cmd, char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    cmd->in = fd;
    close(fd);
}

void handle_redirect_out(t_command *cmd, char *filename, int append)
{
    int flags;
    if (append) {
        flags = O_WRONLY | O_CREAT | O_APPEND;
    } else {
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    }
    
    int fd = open(filename, flags, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    cmd->out = fd;
    close(fd);
}




void handle_redirections(t_command **command)
{
    t_command *cmd = *command;
    
    while (cmd != NULL) {
        int i = 0;
        int j = 0;
        char *args[1024]; // Assuming a maximum of 1024 arguments
        
        while (cmd->arg[i] != NULL) {
            if (strcmp(cmd->arg[i], "<") == 0) {
                if (cmd->arg[i + 1] != NULL) {
                    handle_redirect_in(cmd, cmd->arg[i + 1]);
                    i += 2; // Skip over both "<" and the filename
                } else {
                    fprintf(stderr, "Syntax error: Missing filename after '<'\n");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(cmd->arg[i], ">") == 0) {
                if (cmd->arg[i + 1] != NULL) {
                    handle_redirect_out(cmd, cmd->arg[i + 1], 0);
                    i += 2; // Skip over both ">" and the filename
                } else {
                    fprintf(stderr, "Syntax error: Missing filename after '>'\n");
                    exit(EXIT_FAILURE);
                }
            } 
            // else if (strcmp(cmd->arg[i], ">>") == 0) {
            //     if (cmd->arg[i + 1] != NULL) {
            //         handle_redirect_out(cmd, cmd->arg[i + 1], 1);
            //         i += 2; // Skip over both ">>" and the filename
            //     } else {
            //         fprintf(stderr, "Syntax error: Missing filename after '>>'\n");
            //         exit(EXIT_FAILURE);
            //     }
            // }
            else {
                args[j++] = cmd->arg[i];
                i++;
            }
        }
        args[j] = NULL; // Terminate the new argument array
        
        // Update the command's arguments
        for (int k = 0; k < j; k++) {
            cmd->arg[k] = args[k];
        }
        cmd->arg[j] = NULL;
        
        cmd = cmd->next;
    }
}


