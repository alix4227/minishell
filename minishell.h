# ifndef MINI_SHELL_H
# define MINI_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int	g_r_code;

typedef struct s_global
{
	int index;
}t_global;

typedef struct s_data
{
	char			*word;
	char			*type;
	int				index;
	char			**args;
	int				i;
	int				j;
	int				k;
	int				len;
	char			*retour;
	struct s_data	*next;
	struct s_data	*back;
}t_data;

typedef struct s_List
{
	struct s_data	*begin;
	struct s_data	*end;
}t_list;

char	*ft_itoa(int n);
char	ft_base(int number);
int		ft_len (int n);
int		ft_strcmp(char *s1, char *s2);
int		get_cmd_nb(t_data *data);
void	ft_first_cmd(int **pipefd, int i);
void	ft_middle_cmd(int **pipefd, int i);
void	ft_last_cmd(int **pipefd, int i);
void	ft_close_all_pipes(int **pipefd, t_data *data, t_list *list);
int		is_redir_in(t_data *data);
void	ft_redir_in(t_data *data);
int		is_redir_out(t_data *data);
void	ft_redir_out(t_data *data);
int		is_redirections(t_data *data);
void	exec(t_list *list, char **env, t_global global);
int		ft_strlen(char const *args);
char	*ft_realloc(char *expanded, char *retour, t_data *data);
int		is_quote(char c);
int		is_digit(char c);
int		is_operator(char c);
int		ft_strchr(char *left_char, char c);
char	*ft_strdup(char *s1);
char	*ft_strcat(char const *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen_cmd(t_data *data);
void	print_list(t_list *list, char *args);
char	*get_var_name(char *retour);
char	*get_expand(char *retour);
void	free_list(t_list *list);
void	node_creation(t_list *list, char *retour);
void	get_file(t_list *list);
int		is_operator2(char *word);
void	fill_args_cmd(t_data *data, int k);
void	get_args_cmd(t_data *data, t_list *list);
int		is_cmd(char *word, t_data *data);
void	get_type(t_data *data, t_list *list);
void	space_pars(t_list *list, t_data *data);
void	operator_pars(t_list *list, t_data *data, char *args);
void	single_quote_pars(t_data *data, char *args);
void	expansion(t_data *data, char *args);
void	double_quotes_expansion(t_data *data, char *args);
void	double_quotes_pars(t_data *data, char *args);
void	return_code(t_data *data, char *args, t_global global);
void	dollar_pars(t_data *data, char *args, t_global global);
void	get_word(t_list *list, char *args, t_data *data, t_global global);
void	initialisation(t_data *data, char *args, char **env);
void	search_redir(t_data * data);
int		is_redir_out_append(t_data *data);
void	ft_redir_out_append(t_data *data);
void	*ft_memset(void *str, int c, size_t len);
int		signal_handlers(t_global global);
void	signal_handler(int signum);
void	is_redir_start(t_data * data);
int		is_error(char *args);
int		is_error_2(t_data *data, t_list *list);
int		is_unclosed_quotes(char *args);
int		check_path_cmd(char *word);
int		build_check_path_cmd(char *word, t_data *data, int i, int j);
char	*build_path(char *cmd, char *word);
int		is_chevrons(t_data *data);
void	dollar_pars_digit_quote(t_data *data, char *args);
void	free_args_cmd(t_data *temp, int i);
#endif