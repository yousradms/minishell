/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:56:00 by ydoumas           #+#    #+#             */
/*   Updated: 2024/07/01 16:59:17 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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

char *find_commande(char *cmd, char **envp)
{
    int i;
    char **paths;
    char *path;
    char *part_path;
    int j;
    
    if (cmd[0] == '/' || cmd[0] == '.')
        return cmd;
    i = 0;
    while (envp[i] && strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    if (!envp[i])
        return NULL;
    paths = ft_split4(envp[i] + 5, ':');//"PATH="
    i = 0;
    while (paths[i])
    {
        part_path = strjoin(paths[i], "/");
        path = strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
        {
            j = 0;
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

void handle_multiple_command(t_command **commande, char **env)
{
    t_command *cmd = *commande;
    pid_t pid;
    int fd[2], prev_fd = -1;
    char *full_command;
    
    while (cmd)
    {
        if (cmd->next != NULL)
        {
            if (pipe(fd) == -1)
            {
                perror("pipe");
                return;
            }
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return;
        }
        else if (pid == 0)
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
            handle_redirections(&cmd);
            for (int i = 0; cmd->arg[i] != NULL; i++)
            {
                char *cleaned_arg = remove_quotes(cmd->arg[i]);
                free(cmd->arg[i]);
                cmd->arg[i] = cleaned_arg;
            }
            if (is_builtin(cmd->arg[0]))
            {
                execute_builtin(&cmd,env);
            }
            else
            {
                full_command = find_commande(cmd->arg[0], env);
                if (full_command == NULL)
                {
                    fprintf(stderr, "Error: find_commande returned NULL\n");
                    exit(EXIT_FAILURE);
                }
                if (execve(full_command, cmd->arg, env) == -1)
                {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            if (prev_fd != -1)// Parent process
                close(prev_fd);
            if (cmd->next != NULL)
            {
                close(fd[1]);
                prev_fd = fd[0];
            }
            wait(NULL); // Wait for the child process to finish
        }
        cmd = cmd->next;
    }
    while (wait(NULL) > 0);// Wait for all remaining child processes
}




