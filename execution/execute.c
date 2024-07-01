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
// Function to handle concatenated command and arguments
void handle_concatenated_args(char **arg)
{
    for (int i = 0; arg[i] != NULL; i++)
    {
        // If the argument contains quotes but no space
        char *quote_pos = strchr(arg[i], '"');
        if (quote_pos != NULL)
        {
            // Remove quotes
            memmove(quote_pos, quote_pos + 1, strlen(quote_pos));
            char *end_quote_pos = strchr(quote_pos, '"');
            if (end_quote_pos != NULL)
            {
                memmove(end_quote_pos, end_quote_pos + 1, strlen(end_quote_pos));
            }
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to join two strings with a "/" in between
char *strjoin(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = malloc(len1 + len2 + 2); // +2 for '/' and '\0'

    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(result, str1);
    result[len1] = '/';
    strcpy(result + len1 + 1, str2);

    return result;
}

// Function to search for a command in the environment paths
// char *search_command(const char *command, char **env) {
//     // Get the PATH environment variable
//     char *path_env = NULL;
//     for (int i = 0; env[i] != NULL; i++) {
//         if (strncmp(env[i], "PATH=", 5) == 0) {
//             path_env = env[i] + 5;
//             break;
//         }
//     }

//     if (!path_env) {
//         fprintf(stderr, "PATH environment variable not found\n");
//         return NULL;
//     }

//     // Split the PATH variable into individual paths
//     size_t path_len = strlen(path_env);
//     char *start = path_env;
//     char *end = path_env;

//     while (end < path_env + path_len) {
//         // Find the next colon or end of string
//         while (*end != ':' && *end != '\0') {
//             end++;
//         }

//         // Temporarily terminate the current path
//         if (*end == ':') {
//             *end = '\0';
//         }

//         // Join the current path with the command
//         char *full_path = strjoin(start, command);

//         // Check if the command exists and is executable
//         if (access(full_path, X_OK) == 0) {
//             return full_path;
//         }

//         free(full_path);

//         // Move to the next path
//         if (*end == '\0') {
//             break;
//         }
//         start = end + 1;
//         end = start;
//     }

//     return NULL;
// }

char *find_commande(char *cmd, char **envp)
{
    if (cmd[0] == '/' || cmd[0] == '.')
        return cmd;
    int i = 0;
    while (envp[i] && strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    if (!envp[i])
        return NULL;
    char **paths = ft_split4(envp[i] + 5, ':');//"PATH="
    i = 0;
    char *path;
    while (paths[i]) {
        char *part_path = strjoin(paths[i], "/");
        path = strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0) {
            int j = 0;
            while (paths[j])
                free(paths[j++]);
            free(paths);
            return path;
        }
        free(path);
        i++;
    }
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
    return NULL;
}
void execute_one_command(t_command **command,char **env)
{
    // pid_t pid;
    // int status;
    (void)env;
    if (command == NULL || *command == NULL)
    {
        fprintf(stderr, "No command to execute\n");
        return;
    }
    //handle builtins
    if (is_builtin((*command)->arg[0]))
    {
        //printf("7777");
        execute_builtin(command,env);
        return;
    }
    ////Task : handle redirections////
    //Step 1: Fork a Child Process
    // pid = fork();//<0-->error =0-->child process
    // //>0 parent process
    // if (pid < 0)
    // { 
    //     perror("fork");
    //     exit(1);
    // }
    // else if (pid == 0)
    // {
    //     // Check if the command path is valid
    //     char *full_command = find_commande((*command)->arg[0],env);
    //     // Child process
    //     //printf("%s", full_command);
    //     if (execve(full_command, (*command)->arg, env) == -1)
    //     {
    //         //printf("######");
    //         perror("execve");
    //         exit(EXIT_FAILURE);
    //     }
    // }
    // else
    // { 
    //     // Parent process
    //     waitpid(pid, &status, WUNTRACED);
    // }
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
void execute(t_command **commande,char **env)
{
    int nbrElem;
    nbrElem = count_nbr_command(*commande);
    //printf("##Nbr elements:[%d]##\n", nbrElem);
    if(nbrElem == 1)
    {
        execute_one_command(commande,env);
        //print_command(commande);
    }
    else
    {
        ////Task : handle pipes////
    }
}