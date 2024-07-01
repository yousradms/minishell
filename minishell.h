/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydoumas <ydoumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/28 17:53:05 by ydoumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define w_count 1000
#define L_count 1000

typedef enum s_type
{
    WSPACE = 1,
    PIPE = 2,
    REDIN = 3,//<
    REDOUT = 4,//>
    APPEND = 5,//>>
    HEREDOC = 6,//<<
    SIGN = 7,//$
    EXIT_STATUS = 8,//$?
    WORD = 9,//
    SQUOTE = 10,//
    DQUOTE = 11//
    
} t_type;

typedef enum s_state
{
    GENERAL = 1,
    DQ = 2,
    SQ = 3
} t_state;

typedef struct s_node
{
    char *content;
    t_type type;
    t_state state;
    struct s_node *next;
    struct s_node *prev;
} t_node;

typedef struct s_command
{
    char *cmd;
    char **arg;
    char **red;//< > append file.txt
    //heredoc
    struct s_command *next;
} t_command;
typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
    struct s_env *prev;
} t_env;

//parsing
int	ft_strlen(char *str);
char	**ft_split(char *s);
t_node *create_node(char *content, int type,int state);
void add_node(t_node **head, t_node *node);
void free_precedent_nodes(t_node *head);
void print_list(t_node *head);
void parsing(t_node **head);
int ft_error(t_node **head);
t_node	*ft_lstlast(t_node *lst);
void count_quotes(char *s);
void add_double_delimiters(char *s, int *i, int *len,char c1,char c2);
void add_one_delimiters(char *s, int *i, int *len, char c);
void add_double_quote_delimiters(char *s, int *i, int *len);
void add_single_quote_delimiters(char *s, int *i, int *len);
char *add_delimiter(char *s);
void tokenize(char *s,t_node **head,t_state state);
int just_spaces(char *s);
char* replace_env_variables(char* input, char **env);
void expanding(t_node *list, char **env);
char *remove_quotes(char *s);
int contain_env(char *s);
t_state get_state(char *s);
void free_arg(char **result);
t_command *ft_split2(t_node **head);
void print_list2(t_command *command);
void execute(t_command **command,char **env);
int count_elem_command(t_command *command);

void handle_herdoc(t_node *head);
int double_dquote_before(char *s,int i);
int simple_squote_after(char *s,int i);
char	*ft_strjoin(char *s1, char	*s2);
char **fill_arg(char *str);
char    **ft_split3(char *str);
//execution
int count_nbr_command(t_command *command);
void execute(t_command **commande,char **env);
void execute_one_command(t_command **command,char **env);
void handle_concatenated_args(char **arg);
void ft_cd(t_command **command);
int is_builtin(char *cmd);
void execute_builtin(t_command **command,char **envp);
void ft_echo(t_command **cmd);
void ft_env(t_command **command, t_env **envp);
void ft_exit(t_command **command);
void ft_export(t_command **command);
// void ft_pwd(t_command **command);
void ft_pwd(t_command **command, t_env **envp);
void ft_unset(t_command **command);
char *search_command(const char *command, char **env);
char	**ft_split4( char *s, char c);
char	*strndup1( char *s, size_t n);
void set_ennv(t_env **envp, const char *var, const char *value);

#endif