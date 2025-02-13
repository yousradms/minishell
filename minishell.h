/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/09 20:57:10 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <termios.h>
# include <errno.h>
# include <dirent.h>

# define W_COUNT 5000
# define L_COUNT 5000
# define MAX_WORDS 1000
# define MAX_LENGTH 1000
# define NAME "minishell: "
# define ERR_PIPE "syntax error near unexpected token `|'"
# define ERR_FILE "syntax error near unexpected token `'"

int	g_global;

typedef enum s_type
{
	WSPACE = 1,
	PIPE = 2,
	REDIN = 3,
	REDOUT = 4,
	APPEND = 5,
	HEREDOC = 6,
	SIGN = 7,
	WORD = 9,
	DELIMITER = 10,
	D_DOLLAR = 11,
}	t_type;

typedef enum s_state
{
	GENERAL = 1,
	DQ = 2,
	SQ = 3
}	t_state;

typedef struct s_node
{
	char			*content;
	t_type			type;
	t_state			state;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_command
{
	char				*cmd;
	char				**arg;
	int					my_fd;
	int					in;
	int					out;
	int					append;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_args
{
	int		i;
	int		i2;
	int		i3;
	char	quoat;
}	t_args;

typedef struct s_args1
{
	int		i;
	int		i2;
	int		i3;
	char	quote;
}	t_args1;

typedef struct s_expansion_data
{
	int		*i;
	int		*j;
	char	**var_name;
	char	**expanded;
}	t_expansion_data;

char		**parsing_execute_command(char **line, char **env);
void		add_single_quote_delimiters(char *s, char *new_s, int *i, int *j);
void		add_double_quote_delimiters(char *s, char *new_s, int *i, int *j);
void		add_one_delimiters(char *new_s, int *i, int *j, char c);
void		add_one_delimiters_before(char *new_s, int *i, int *j, char c);
void		add_double_delimiters(char *new_s, int *i, int *j, char c1);
char		*add_delimiter(char *s);
void		tokenize(char *s, t_node **head, t_state state);
char		**ft_split(char *s);
int			contain_env(char *s);
int			is_valid_char(char c);
int			contain_home_after_quote(char *s);
void		expand_home_directory(t_node *current);
char		*extract_variable_name(char *expanded, int i, int j);
void		replace_numeric_variable(char **expanded, int *i, int j);
void		process_variable(char **expanded, int *i, int *j, char **env);
void		set_expanded(char **str, char **content, char **env);
void		expand_variable(t_node *current, char **env);
char		*replace_variable(char *str, char *value, int start, int end);
void		set_value(t_expansion_data *data, char **env);
void		expanding(t_node *list, char **env);
char		**ft_split3(char *str);
t_command	*ft_split2(t_node **head);
char		*initialize_command_line(void);
int			finalize_command(t_command **result, char *line);
int			parsing(t_node *head, char **env);
void		open_here(t_node *token, t_node *ptr_err, char **env);
void		handle_herddoce(t_command **command, char **env);
int			handle_herdoc(char *delimiter, char **env);
void		add_back(t_command **head, t_command *new_node);
t_command	*create_new_command(char *line);
int			add_new_command_to_result(t_command **result, char **line);
void		free_commands(t_command *commands);
void		free_arg(char **result);
int			check_quot(char *line, char a, char b);
char		*remove_quotes(char *s);
t_node		*create_node(char *content, int type, int state);
void		add_node(t_node **head, t_node *node);
void		free_precedent_nodes(t_node *head);
char		**set_env(char **env);
int			just_spaces(char *s);
t_state		get_state(char *s);
char		**env_to_char_array(t_env *env);
int			count_nbr_commands(t_command *cmd);
char		*ft_strjoin(char *s1, char	*s2);
char		*ft_strtrim(char *s1, char *set);
void		sigint_handler(int signo);
void		ft_cd(t_command **command, t_env **envp);
int			is_builtin(char *cmd);
char		**execute_builtin(t_command **command, char **envp);
void		ft_echo(t_command **cmd);
void		ft_env(t_env **envp);
void		ft_exit(t_command **command);
void		ft_export(t_command **command, t_env **envp);
void		ft_pwd(void);
void		ft_unset(char *var_names[], int num_vars, t_env **envp);
void		update_oldpwd(t_env **envp, char *oldpwd);
void		update_pwd(t_env **envp, char *newpwd);
char		**ft_split4( char *s, char c);
char		*strndup1( char *s, size_t n);
char		*find_commande(char *cmd, char **envp);
char		**execute(t_command **commande, char **env);
char		**handle_one_command(t_command **commande, char **env);
void		handle_quotes_ex(t_command **cmd);
void		execute_one_command(t_command **commande, char **env);
void		handle_redirect_in(t_command *cmd, char *filename);
void		handle_redirect_out(t_command *cmd, char *filename, int append);
void		handle_redirections(t_command *cmd);
char		**handle_multiple_command(t_command **commande, char **env);
void		handle_output_redirection(t_command *cmd, int *index);
void		handle_append_redirection(t_command *cmd, int *index);
void		handle_input_redirection(t_command *cmd, int *index);
void		handle_heredoc_redirection(t_command *cmd, int *index);
void		handle_exit_status(int status);
char		*exit_s(int new_one, int set);
void		free_char_array(char **array);
void		free_env_node(t_env *node);
void		free_paths(char **paths);
void		remove_redirection_symbols(char **args, int index);
void		free_env_list(t_env *head);
t_env		*create_env_node(char *var, char *value);
void		append_env_node(t_env **head, t_env **last, t_env *new_env);
void		add_new_env(t_env **envp, char *key, char *value);
void		env_list(t_env **env, char **envp);
int			cd_previous(t_env **envp);
int			cd_to_dir(const char *dir);
int			cd_home(const char *home);
int			get_current_directory(char *dir, size_t size);
void		update_existing_env(t_env *env, char *arg, char *value);
int			is_valid(char c);
int			check_arg(char *var);
char		*extract_var(char *line);
char		*extract_value(char *line);
void		sigint_handler_herdoc(int signo);
void		export_expand(t_node **head);
void		wait_for_all_processes(pid_t *pids, int cmd_count);
void		print_cmd_not_found(char *s);
char		*get_env_value(char *var_name, char **env);
int			contain_home1(char *s);
char		*extract_variable_name(char *expanded, int i, int j);
void		replace_numeric_variable(char **expanded, int *i, int j);
char		*handle_specific_cases(char c);
void		handle_special_cases(char **expanded, int *i, int *j, char **env);
int			validate_inputs(char **expanded, int *i, int *j, char **env);
void		replace_special_variable(char **expanded, \
int *i, int j, char *value);
int			del_without_quotes(char *s);
int			setup_temp_files(int *temp_fd);
int			is_end_of_heredoc(char *line, char *s);
void		process_heredoc_input(int fd, char *s, int flag, char **env);
int			determine_flag(char *delimiter);
int			is_whitespace(char c);
void		free_tab(char **tab, int size);
void		handle_double_quote(char *str, char **tab, t_args1 *a);
void		handle_single_quote(char *str, char **tab, t_args1 *a);
void		add_limiter_type(t_node **head);
void		add_double_dollar_delimiters(char *new_s, int *i, int *j);
void		remove_dollor_quotes_delimiter(t_node **list);
char		*clean_argument(char *arg);
void		check_access_errors(t_command *cmd, const char *full_command);
void		wait_for_child_process(pid_t pid);
char		**handle_builtin_command(t_command **commande, char **env);
void		handle_child_process(t_command **commande, char **env);
char		**process_pipe(t_command *cmd, char **env, pid_t *pids);
char		**execute_command(t_command *cmd, char **env);
char		*prepare_line(char **line);
void		tokenize_line(t_node **head, char **result);
void		free_resources(char **result, t_node *head, char *s);
void		remove_dollor_quotes(t_node **list);
t_node		*process_current_node(t_node *current, char **env);
char		*allocate_new_string(int new_len);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
void		ft_putstr_fd(char *s, int fd);
char		*ft_itoa(int n);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strchr(const char *string, int searchedChar);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
char		*ft_strdup(char *src);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlcpy(char *dest, const char *src, int size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strncpy(char *dest, char *src, int n);
char		*ft_strnstr(const char *str, const char *to_find, size_t n);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			symbol_redirect_bef(t_node *current, char **env);
char		**get_env(void);
char		*get_home_from_env(t_env **envp);
void		update_directories(t_env **envp, char *oldpwd, char *cwd);
void		handle_cd_error(int status);
int			validate_argument(char *arg);
int			empty_contain_space(t_node *current, char **env);
int			check_sign_and_skip(char **trimmed);

#endif
