/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:56:00 by ydoumas           #+#    #+#             */
/*   Updated: 2024/07/22 17:26:20 by ksellami         ###   ########.fr       */
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
    if(!cmd || strcmp(cmd,"") == 0)
        return(0);
    return (cmd[0] == '/' || cmd[0] == '.');
}

static char **get_paths_from_env(char **envp)
{
    int i;
    if (!envp)
        return NULL;
    i = 0;
    while (envp[i] && strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    if (!envp[i])
        return (NULL);
    return (ft_split4(envp[i] + 5, ':')); // "PATH="
}

static char *build_full_path(char *dir, char *cmd)
{
    if (!dir || !cmd)
        return NULL;
    char *part_path;
    char *full_path;

    part_path = strjoin(dir, "/");
    if (!part_path)
        return NULL;
    full_path = strjoin(part_path, cmd);
    free(part_path);
    return full_path;
}

static void free_paths(char **paths)
{
    int i;
    if (!paths)
        return;
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

    if (!cmd || strcmp(cmd,"") == 0)
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
        if (!path)
        {
            free_paths(paths);
            return NULL;
        }
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




static  void execute_command(t_command *cmd, char **env)
{
    char *full_command;

    // handle_redirections(&cmd);
    //handle_quotes_ex(&cmd);
    if (is_builtin(cmd->arg[0]))
    {
        execute_builtin(&cmd, env);
        //return ;
    }
    // else
    // {
    full_command = find_commande(cmd->arg[0], env);
    if (full_command == NULL)
    {
        //fprintf(stderr, "Error: find_commande returned NULL\n");
        fprintf(stderr,"Minishell: %s: command not found\n",cmd->arg[0]);
        exit(EXIT_FAILURE);
    }
    if (execve(full_command, cmd->arg, env) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }

}


pid_t fork_process()
{
    pid_t pid = fork();
    if (pid == -1)
        perror("fork");
    return (pid);
}
static int count_nbr_commands(t_command *cmd)
{
    int count =0;
    while(cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return(count);
}
// char **handle_multiple_command(t_command **commande, char **env)
// {
//     t_command *cmd;
//     pid_t pid;
//     int fd[2];
//     int i;
    

//     cmd = *commande;
//     while (cmd)
//     {
//         if (cmd->next != NULL && pipe(fd) == -1)
//             return(env); // return NULL on error
//         pid = fork();
//         if (pid == -1)
//             return(NULL); // return NULL on error
//         else if (pid == 0)
//         {
//             handle_redirections(cmd);
//             if (cmd->next)
//             {
//                 close(fd[0]);
//                 if (cmd->out == 1)
//                     dup2(fd[1], 1);
//                 close(fd[1]);
//             }
//             execute_command(cmd, env);
//         }
//         else
//         {
//             if (cmd->next)
//             {
//                 close(fd[1]);
//                 dup2(fd[0], STDIN_FILENO);
//                 close(fd[0]);
//             }
//         }
//         cmd = cmd->next;
//     }
//             waitpid(pid, 0, 0);
//     return(env);
// }

char **handle_multiple_command(t_command **commande, char **env)
{
    t_command *cmd;
    pid_t *pids;
    int fd[2];
    int i, cmd_count;

    cmd = *commande;
    cmd_count = count_nbr_commands(cmd);

    pids = (pid_t *)malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
        return NULL; // Handle memory allocation failure

    i = 0;
    while (cmd)
    {
        if (cmd->next != NULL && pipe(fd) == -1)
        {
            free(pids);
            return env; // return env on error
        }

        pids[i] = fork();
        if (pids[i] == -1)
        {
            free(pids);
            return NULL; // Handle fork failure
        }
        else if (pids[i] == 0)
        {
            handle_redirections(cmd);
            if (cmd->next)
            {
                close(fd[0]);
                if (cmd->out == 1)
                    dup2(fd[1], 1);
                close(fd[1]);
            }
            execute_command(cmd, env);
            //exit(0); // Ensure the child process exits after executing the command
        }
        else
        {
            if (cmd->next)
            {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
            }
        }
        cmd = cmd->next;
        i++;
    }
    int j = 0;
    while (j < cmd_count)
    {
        waitpid(pids[j], NULL, 0);
        j++;
    }
    free(pids);
    return env;
}

