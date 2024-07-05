/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:56:00 by ydoumas           #+#    #+#             */
/*   Updated: 2024/07/05 12:12:24 by ksellami         ###   ########.fr       */
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

static void setup_child_process(t_command *cmd, int prev_fd, int fd[2])
{
    if (prev_fd != -1)
    {
        dup2(prev_fd, 0);
        close(prev_fd);
    }
    if (cmd->next != NULL)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
    }
}

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

static void parent_process_actions(int *prev_fd, int fd[2], t_command *cmd)
{
    if (*prev_fd != -1)
        close(*prev_fd);
    if (cmd->next != NULL)
    {
        close(fd[1]);
        *prev_fd = fd[0];
    }
    wait(NULL);
}

pid_t fork_process()
{
    pid_t pid = fork();
    if (pid == -1)
        perror("fork");
    return (pid);
}

void handle_multiple_command(t_command **commande, char **env)
{
    t_command *cmd;
    pid_t pid;
    int prev_fd;
    int fd[2];

    cmd = *commande;
    prev_fd = -1;
    while (cmd)
    {
        if (cmd->next != NULL && !create_pipe(fd))
            return;
        pid = fork_process();
        if (pid == -1)
            return;
        else if (pid == 0)
        {
            setup_child_process(cmd, prev_fd, fd);
            execute_command(cmd, env);
        }
        else
            parent_process_actions(&prev_fd, fd, cmd);
        cmd = cmd->next;
    }
    while (wait(NULL) > 0);
}




