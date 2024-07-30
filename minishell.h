/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/07/29 16:46:38 by ksellami         ###   ########.fr       */
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
#include <limits.h>
#include <signal.h>
#include<stdbool.h>
#include <errno.h>
#define w_count 1000
#define L_count 1000
#define MAX_WORDS 1000
#define MAX_LENGTH 1000
# define NAME "minishell: "
# define ERR_PIPE "syntax error near unexpected token `|'\n"
# define ERR_FILE "syntax error near unexpected token `'\n"
#define BUFFER_SIZE 1024


typedef enum s_type
{
	
	WSPACE = 1,
	PIPE = 2,
	REDIN = 3,//<
	REDOUT = 4,//>
	APPEND = 5,//>>
	HEREDOC = 6,//<<
	SIGN = 7,//$
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
	int my_fd;
	int in;
	int out;
	int append;
	struct s_command *next;
	struct s_command *prev;
} t_command;

typedef struct s_env
{
	char *var;
	char *value;
	struct s_env *next;
	struct s_env *prev;
} t_env;

typedef struct s_args
{
	int i;
	int i2;
	int i3;
	char quoat;

}	t_args;

typedef struct s_args1
{
	int i;
	int i2;
	int i3;
	char quote;
} t_args1;

///PARSING///
char **parsing_execute_command(char **line,char **env);

//tokenize
void add_single_quote_delimiters(char *s, char *new_s, int *i, int *j);
void add_double_quote_delimiters(char *s, char *new_s, int *i, int *j);
void add_one_delimiters(char *new_s, int *i, int *j, char c);
void add_one_delimiters_before(char *new_s, int *i, int *j, char c);
void add_double_delimiters(char *new_s, int *i, int *j, char c1, char c2);
char *add_delimiter(char *s);
void tokenize(char *s,t_node **head,t_state state);
char	**ft_split(char *s);

//expanding
int contain_env(char *s);
int is_valid_char(char c);
int contain_home_after_quote(char *s);
void expand_home_directory(t_node *current);
char *extract_variable_name(char *expanded, int i, int j);
void replace_numeric_variable(char **expanded, int *i, int j);
void process_variable(char **expanded, int *i, int *j, char **env);
void set_expanded(char **str, char **content, char **env);
void expand_variable(t_node *current, char **env);
char *replace_variable(char *str, char *value, int start, int end);
void set_value(int *i, int *j, char **var_name, char **expanded, char **env);
void expanding(t_node *list, char **env);

//parser 
char **ft_split3(char *str);
t_command *ft_split2(t_node **head);
char *initialize_command_line();
int finalize_command(t_command **result, char *line);

//error_syntax
int parsing(t_node *head,char **env);
void open_here(t_node *token, t_node *ptr_err, char **env);

//heredoc
void handle_herddoce(t_command **command, char **env);
int handle_herdoc(char *delimiter, char **env);

//utilsp
void add_back(t_command **head, t_command *new_node);
t_command *create_new_command(char *line);
int add_new_command_to_result(t_command **result, char **line);
void free_commands(t_command *commands);
void free_arg(char **result);
int	check_quot(char *line, char a, char b);
char *remove_quotes(char *s);
char *remove_dquotes(char *s);
char *remove_squotes(char *s);
t_node *create_node(char *content, int type,int state);
void add_node(t_node **head, t_node *node);
void free_precedent_nodes(t_node *head);
char **set_env(char **env);
int just_spaces(char *s);
t_state get_state(char *s);
char  **env_to_char_array(t_env *env);
int count_nbr_commands(t_command *cmd);

//debug
void print_list(t_node *head);
void print_list2(t_command *command);
void print_darg(char **s);

//libft_utils.c
char	*ft_strjoin(char *s1, char	*s2);
char	*ft_strtrim(char  *s1, char  *set);

//signals
void    sigint_handler(int signo);

///EXECUTION///

//builtins
void ft_cd(t_command **command, t_env **envp);
int is_builtin(char *cmd);
char **execute_builtin(t_command **command, char **envp);
void ft_echo(t_command **cmd);
void ft_env(t_env **envp);
void ft_exit(t_command **command);
void ft_export(t_command **command, t_env **envp);
void ft_pwd(void);
void ft_unset(char *var_names[], int num_vars, t_env **envp);
void update_oldpwd(t_env **envp, char *oldpwd);
void update_pwd(t_env **envp, char *newpwd);

//execute
char	**ft_split4( char *s, char c);
char	*strndup1( char *s, size_t n);
char *find_commande(char *cmd, char **envp);
char **execute(t_command **commande, char **env);
char **handle_one_command(t_command **commande,char **env);
pid_t fork_process();
void handle_quotes_ex(t_command **cmd);
void execute_one_command(t_command **commande, char **env);

//redirections
void handle_redirect_in(t_command *cmd, char *filename);
void handle_redirect_out(t_command *cmd, char *filename, int append);
void handle_redirections(t_command *cmd);
char **handle_multiple_command(t_command **commande, char **env);
void handle_output_redirection(t_command *cmd, int *index);
void handle_append_redirection(t_command *cmd, int *index);
void handle_input_redirection(t_command *cmd, int *index);
void handle_heredoc_redirection(t_command *cmd, int *index);

void setup_signal_handlers();
void handle_ctrl_d(void);
void handle_exit_status(int status);
//exit_status
char* exit_s(int new_one, int set);

//utilse
void free_char_array(char **array);
void free_env_node(t_env *node);
void free_paths(char **paths);
void remove_redirection_symbols(char **args, int index);
void free_env_list(t_env *head);

t_env *create_env_node(char *var, char *value);
void append_env_node(t_env **head, t_env **last, t_env *new_env);
void add_new_env(t_env **envp, char *key, char *value);
void env_list(t_env **env, char **envp);
void cd_previous(t_env **envp);
void cd_to_dir(const char *dir);
void cd_home(const char *home);
int get_current_directory(char *dir, size_t size);
void update_existing_env(t_env *env,char *arg, char *value);
int is_valid(char c);
int check_arg(char *var);
char *extract_var(char *line);
char *extract_value(char *line);
void    sigint_handler_herdoc(int signo);
void export_expand(t_node **head);

#endif
