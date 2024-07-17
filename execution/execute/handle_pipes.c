/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:56:00 by ydoumas           #+#    #+#             */
/*   Updated: 2024/07/15 18:39:23 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to join two strings with a "/" in between
char *strjoin(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = malloc(len1 + len2 + 2); // +2 for '/' and '\0'
    if (!result)
        exit(EXIT_FAILURE);
    strcpy(result, str1);
    result[len1] = '/';
    strcpy(result + len1 + 1, str2);
    return result;
}

static int is_absolute_or_relative_path(char *cmd)
{ 
    if(!cmd)
        return(0);
    return (cmd[0] == '/' || cmd[0] == '.');
}

static char **get_paths_from_env(char **envp)
{
    int i;
    
    i = 0;
    while (envp[i] && strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    if (!envp[i])
        return (NULL);
    return (ft_split4(envp[i] + 5, ':')); // "PATH="
}

static char *build_full_path(char *dir, char *cmd)
{
    char *part_path;
    char *full_path;

    part_path = strjoin(dir, "/");
    full_path = strjoin(part_path, cmd);
    free(part_path);
    return full_path;
}

static void free_paths(char **paths)
{
    int i;
    
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
}

char *find_commande(char *cmd, char **envp)
{
    int i;
    char **paths;
    char *path;

    if (!cmd)
        return(NULL);
    if (is_absolute_or_relative_path(cmd))
        return (cmd);
    paths = get_paths_from_env(envp);
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        path = build_full_path(paths[i], cmd);
        if (access(path, F_OK) == 0)
        {
            free_paths(paths);
            return (path);
        }
        free(path);
        i++;
    }
    free_paths(paths);
    return (NULL);
}

static int create_pipe(int fd[2])
{
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (0);
    }
    return (1);
}
#include<stdbool.h>
bool has_output_redirection(t_command *cmd)
{
    return(cmd->out != 1);
    //return(strchr(cmd->cmd,'>') != NULL);
}
// static void setup_child_process(t_command *cmd,int fd[2])
// {
//     int pid = fork();
//     if (pid == 0)
//     {
//         close(fd[0]);
//         if (cmd->next && has_output_redirection(cmd))
//             dup2(fd[1], 1);
//         close(fd[1]);
//     }
// }

static  void execute_command(t_command *cmd, char **env)
{
    char *full_command;
    
    handle_redirections(&cmd);
    // for (int i = 0; cmd->arg[i] != NULL; i++) {
    //     char *cleaned_arg = remove_quotes(cmd->arg[i]);
    //     free(cmd->arg[i]);
    //     cmd->arg[i] = cleaned_arg;
    // }
    handle_quotes_ex(&cmd);
    if (is_builtin(cmd->arg[0]))
        execute_builtin(&cmd, env);
    else
    {
        full_command = find_commande(cmd->arg[0], env);
        if (full_command == NULL)
        {
            //fprintf(stderr, "Error: find_commande returned NULL\n");
            printf("Minishell: %s: command not found\n",cmd->arg[0]);
            exit(EXIT_FAILURE);
        }
        if (execve(full_command, cmd->arg, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
}

// static void parent_process_actions(int fd[2], t_command *cmd)
// {
//     // (void)cmd;
//     close(fd[1]);
//     if (cmd-> next)
//         dup2(fd[0],0);
//     close(fd[0]);
    
// }

pid_t fork_process()
{
    pid_t pid = fork();
    if (pid == -1)
        perror("fork");
    return (pid);
}

char **handle_multiple_command(t_command **commande, char **env)
{
    t_command *cmd;
    pid_t pid;
    int prev_fd;
    int fd[2];

    cmd = *commande;
    prev_fd = -1;
    int i = dup(STDIN_FILENO);
    int j = dup(STDOUT_FILENO);
    while (cmd)
    {
        if (cmd->next != NULL && !create_pipe(fd))
            return(env);
        pid = fork_process();
        handle_redirections(&cmd);
        if (pid == -1)
            return(env);
        else if (pid == 0)
        {
            // setup_child_process(cmd, fd);
            close(fd[0]);
            if (cmd->next)
                dup2(fd[1], 1);
            close(fd[1]);
            execute_command(cmd, env);
        }
        else
        {
            close(fd[1]);
            if (cmd-> next)
                dup2(fd[0],0);
            close(fd[0]);
            // parent_process_actions( fd, cmd);
        }

        cmd = cmd->next;
    }
    dup2(j, STDOUT_FILENO);
    dup2(i, STDIN_FILENO);
    close(i);
    close(j);
    waitpid(pid , 0, 0);
    return(env);
}



