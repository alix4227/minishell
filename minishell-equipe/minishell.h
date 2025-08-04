/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/21 09:33:42 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/21 09:33:42 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_data
{
	int				saved_stdin;
	int				original_stdout;
	char			*word;
	char			*type;
	int				index;
	int				redir_check;
	int				ind;
	char			**args;
	int				flag;
	int				is_quote;
	int				i;
	int				j;
	int				k;
	int				len;
	int				stdout;
	char			**env_child_process;
	int				cmds_numb;
	int				here_doc_fd;
	int				heredoc_exit;
	char			*retour;
	int				**pipefd;
	struct s_data	*next;
	struct s_data	*back;
}			t_data;

typedef struct s_gc
{
	void				*ptdr;
	struct s_gc			*next;
}			t_gc;

typedef struct s_List
{
	struct s_data	*begin;
	struct s_data	*end;
}			t_list;

typedef struct s_env
{
	char			*value;
	char			*key;
	struct s_env	*next;
	struct s_env	*back;
}			t_env;

typedef struct s_List_env
{
	struct s_env	*begin;
	struct s_env	*end;
}			t_list_env;

t_list_env	*set_get_env(t_list_env *env);

// exec..execution
void		get_file(t_list *list);
int			is_redirections(t_data *data);
void		exec(t_list *list, t_list_env *env_list);
void		pids_handler(pid_t *pid, int cmds_numb);
void		last_pid_handler(int status);

// exec ../expansion
char		*get_var_name(char *retour);
char		*get_expand(char *retour, t_list_env *env);
void		operator_pars(t_list *list, t_data *data, char *args,
				int *is_quote);
void		single_quote_pars(t_data *data, char *args, int *is_quote);
void		expansion(t_data *data, char *args, t_list_env *env);
void		double_quotes_expansion(t_data *data, char *args, t_list_env *env);

// exec../path_cmd
int			check_path_cmd(char *word);
char		*build_path(char *cmd, char *word);
int			build_check_path_cmd(char *word, t_data *data, t_list_env *env);
int			is_cmd(char *word, t_data *data, t_list_env *env);

// exec../pipes
void		ft_first_cmd(int **pipefd, int i);
void		ft_middle_cmd(int **pipefd, int i);
void		ft_last_cmd(int **pipefd, int i);
void		ft_close_all_pipes(int **pipefd, t_data *data, t_list *list);
void		pipe_creation(t_data *data, int cmds_numb);
int			child_process_pipe(t_data *data, t_list *list, t_list_env *env_list,
				int i);
void		free_pipes_and_pid(int cmds_numb, t_list *list, pid_t *pid);
void		check_pipes(int i, t_data *data, t_list *list, int cmds_numb);
void		ft_close_unused_pipes_for_child(int **pipefd, int cmds_numb, int current_cmd);

// exec../builtin../echo
void		ft_echo(char **av);
int			is_valid_n_option(char *str);
int			ft_strncmp(char *s1, char *s2, int n);

// exec../builtin../pwd
void		ft_pwd(void);

// exec../builtin../unset
void		ft_unset(t_list_env *envp, char **args);

// exec../builtin../cd
void		ft_cd(char **args, t_list_env *envp);

// exec../builtin../export
void		ft_export(t_list_env *envp, char **args);

// exec../builtin../env
void		ft_env(t_list_env *envp, t_data *data);

// exec../builtin../exit
void		ft_exit(char **args);

//exec../here_doc.c
int			here_doc(t_data *data, t_list_env *env);
int			has_heredoc(t_data *data);
void		process_single_heredoc(t_data *data, t_list_env *env, int fd);
char		*get_current_delimiter(t_data *data);
int			is_last_heredoc(t_data *data);
t_data		*find_next_heredoc(t_data *current);

//exec../expand_heredoc
char		*append_char(char c);
char		*append_str(char *base, char *to_add);
char		*check_dollar(char *line, int *i, t_list_env *env);
char		*expand_line(char *line, t_list_env *env);

// pars../list_creation
void		get_word(t_list *list, char *args, t_data *data, t_list_env *env);
void		node_creation(t_list *list, char *retour, int *is_quote);
void		initialisation(t_data *data, char *args, char **env);
void		initialisation_cmd_numb(t_data *data, t_list *list);
void		does_word_exist(t_data *data, char *retour, int *is_quote);

// pars../list_creation
void		node_creation_env_variables(t_list_env *env_list, char *str);
void		env_value(t_list_env *env_list, char **env);
void		get_env_key(char **env, t_list_env *env_list);
char		*ft_value(char *str);

// pars../parsing_function
void		space_pars(t_list *list, t_data *data, int *is_quote);
void		operator_pars(t_list *list, t_data *data, char *args,
				int *is_quote);
void		single_quote_pars(t_data *data, char *args, int *is_quote);
void		double_quotes_pars(t_data *data, char *args,
				t_list_env *env, int *is_quote);

// pars../args_cmd
int			is_operator2(char *word);
void		fill_args_cmd(t_data *data, int k);
void		get_args_cmd(t_data *data, t_list *list);
int			get_cmd_nb(t_data *data, t_list *list);
int			parse_error_operators(char *args);
int			skip_quotes(char *str, int start, char c);
int			is_double_operator(const char *s);
int			check_after(char *args, int *i);
int			check_after_operator(char *args, int pos);
int			skip_whitespace(char *str, int start);
int			check_args_error(char *args);

// pars../dollar_hanling_functions
void		dollar_pars(t_data *data, char *args, t_list_env *env);
void		dollar_pars_digit_quote(t_data *data, char *args, t_list_env *env);

// pars../get_return_code
void		return_code(t_data *data, char *args);
int			check_delim_after_heredoc(t_data *data);
void		process_heredoc_line(int fd, char *line, t_list_env *env);
void		handle_signel(int sig);
int			handle_cmd_execution(t_data *data, t_list *list,
				t_list_env *env_list);

// pars../print_command_error
int			is_error(char *args);
void		print_error(t_list *list, char *args);

// pars../redirection_in
int			is_redir_in(t_data *data);
void		ft_redir_in(t_data *data);

// pars../redirection_out
int			is_redir_out(t_data *data);
int			is_redir_out2(t_data *data);
void		ft_redir_out(t_data *data);
int			is_redir_out_append(t_data *data);
void		ft_redir_out_append(t_data *data);

// pars../tokenisation
void		get_type(t_data *data, t_list *list, t_list_env *env);
char		*get_token_type(t_data *data, int *cmd_nb, t_list_env *env);

// utils../free_memory
void		free_args_cmd(t_data *temp, int i);
void		free_list(t_list *list);
void		free_env_list(t_list_env *env_list);

//utils../builtins_utils2
void		env_list_add_back(t_list_env *env_list, t_env *new_node);
t_env		*env_list_find(t_list_env *env_list, char *key);
void		split_key_value(char *str, char **key, char **value);
void		add_new_env(t_list_env *envp, char *arg, char *key, char *value);
t_env		*new_env_node(char *str);

//utils../path_cmd_utils
int			is_chevrons(t_data *data);
int			built_cmd_child(char *str);
int			built_cmd_parent(char *str);

// utils../ft_itoa
char		*ft_itoa(int n);
void		ft_char(char number, long i, long nbr, char *str);
int			ft_length(long n);

// utils../minishell_utils
int			ft_strchr(char *left_char, char c);
char		*ft_strdup(char *s1);
char		*ft_strcat(char const *s1, char const *s2);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlen(char const *args);
char		*ft_strstr(char *str, char *to_find);

// utils../minishell_utils2
int			is_operator(char c);
int			ft_strlen_cmd(t_data *data);
void		*ft_memset(void *str, int c, size_t len);
char		*ft_realloc(char *expanded, char *retour, t_data *data);
int			is_operator3(char c);

//utils../minishell_utils3
int			is_quote(char c);
int			is_digit(char c);
int			ft_strcmp(char *s1, char *s2);

//utils../utils_execution
void		get_file(t_list *list);
int			is_redirections(t_data *data);

//utils../utils_here_doc
void		ft_bzero(void *s, int n);
int			get_allocation(char const *s, int start, int len);
void		*ft_calloc(int nmemb, int size);
char		*ft_substr(char const *s, int start, int len);
char		*ft_substr(char const *s, int start, int len);
char		*ft_realloc2(char *expanded, char *retour);

//utils../utils_here_doc2
char		*search_in_env(char *expand, t_list_env *env);
void		exit_clean(int exit_code);

// utils../redirection_checker
int			search_redir(t_data *data, t_list_env *env);
int			search_redir_backward(t_data *data, t_list_env *env);
int			is_redir_start(t_data *data, t_list_env *env, t_list *list);
int			not_check(t_list *list);

// utils../syntax_error_token
int			wrong_token_error(t_data *data, t_list *list);
int			check_delim_after_heredoc(t_data *data);
void		pipe_not_followed_by_cmd(t_data *data, t_list *list);
int			check_file_after_redirout(t_data *data);
int			check_file_after_redirin(t_data *data);
int			last_pipe_not_followed_by_cmd(t_data *data, t_list *list);
int			is_file_readable(t_data *data, t_list *list);
int			is_cmd_type(t_data *data);

// util../builtin_utils
int			is_valid_identifier(char *str);
char		*ft_strndup(char *s, int n);
int			ft_isalnum(int c);

// util../gc
void		*ft_malloc(long long size);
char		*ft_gc_strdup(char *s1);

// util../return_code
int			set_get_exit_status(int exit_code);
void		print_splash_screen(void);
void		test_builtins_child(t_data *data, t_list_env *envp, t_list *list);
void		test_builtins_parents(t_data *data, t_list_env *env, t_list *list);

//utils../utils_execution 
int			is_redirections(t_data *data);
void		get_file(t_list *list);

// signal
int			signal_handlers(void);
void		signal_handler(int signum);

// main
void		main_loop_function(t_list *list, char *args, char **env,
				t_list_env *env_list);
int			is_unclosed_quotes(char *args);
void		initialisation_list(t_list **list);
void		print_exec(t_list *list, char *args, t_list_env *env_list);
int			tokenisation_and_exec(t_list *list, char *args,
				t_list_env *env_list);
void		program_handler(t_list *list, char *args, char **env,
				t_list_env *env_list);
void		initialisation_env_list(t_list_env **env_list);

void		here_doc_cmd(t_data *data);
void		update_existing_env(t_env *existing_node, char *key, char *value);
void		add_new_env(t_list_env *envp, char *arg, char *key, char *value);
void		handle_export_argument(t_list_env *envp, char *arg);
int			parse_error_operators(char *args);
#endif