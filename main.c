# include "minishell.h"
int	g_r_code;
void	print_list(t_list *list, char *args)
{
	t_data *data;
	int	i;
	int j;
	data = list->begin;
	if (!list->begin || is_error(args) ||is_unclosed_quotes(args))
	{
		g_r_code = 0;
		return ;
	}
	printf("bash: %s: command not found", data->word);
	g_r_code = 127;
	printf("\n");
}

void free_list(t_list *list)
{
	t_data *data;
	t_data *temp;
	int i;

	if (!list)
		return;
	data = list->begin;
	while (data)
	{
		temp = data;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
			{
				free(temp->args[i]);
				temp->args[i] = NULL;
				i++;
			}
			free(temp->args);
			temp->args = NULL;
		}
		data = data->next;
		free(temp->word);
		free(temp);
		temp = NULL;
	}
	list->begin = NULL;
	free(list);
	
}

void	get_type(t_data *data, t_list *list)
{
	data = list->begin;
	while (data)
	{
		if (is_cmd(data->word, data))
			data->type = "CMD";
		else if (ft_strcmp(data->word, ">") == 0)
			data->type = "REDIR_OUT";
		else if (ft_strcmp(data->word, "<") == 0)
			data->type = "REDIR_IN";
		else if (ft_strcmp(data->word, ">>") == 0)
			data->type = "REDIR_OUT_APPEND";
		else if (ft_strcmp(data->word, "<<") == 0)
			data->type = "HEREDOC";
		else if (ft_strcmp(data->word, "|") == 0)
			data->type = "PIPE";
		else
			data->type = "ARG";
		data = data->next;
	}
}

void	return_code(t_data *data, char *args, t_global global)
{
	int	i;
	char *code;

	i = 0;
	if (global.index == 1)
		data->retour[data->j++] = '0';
	else
	{
		code = ft_itoa(g_r_code);
		while (code[i])
			data->retour[data->j++] = code[i++];
		free(code);
	}
}

int	is_error(char *args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if ((args[0] == '!' || args[0] == ':') && args[1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	check_file_after_redirin(t_data *data)
{
	struct stat sb;
	if (ft_strcmp(data->type, "REDIR_IN") == 0)
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
		{
			if (stat(data->next->word, &sb) == 0 &&
				S_ISREG(sb.st_mode) &&
				(access(data->next->word, X_OK) == 0))
			{
				printf("bash: %s: No such file or directory \n", data->next->word);
				return (1);
			}
			if (access(data->next->word, X_OK))
				return (0);
			else
			{
				printf("bash: %s: No such file or directory \n", data->next->word);
				return (1);
			}
		}
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	check_file_after_redirout(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_OUT") == 0 || ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
			return (0);
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	pipe_not_followed_by_cmd(t_data *data)
{
	if (ft_strcmp(data->type, "PIPE") == 0)
	{
		if (data->next && ft_strcmp(data->next->type, "CMD") == 0)
			return (0);
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
	
}

int	check_delim_after_heredoc(t_data *data)
{
	if (ft_strcmp(data->type, "HEREDOC") == 0)
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
			return (0);
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	is_error_2(t_data *data, t_list *list)
{
	data = list->begin;
	if (ft_strcmp(list->begin->type, "PIPE") == 0)
	{
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	while (data)
	{
		if (pipe_not_followed_by_cmd(data))
			return (1);
		if (check_file_after_redirout(data))
			return (1);
		if (check_file_after_redirin(data))
			return (1);
		if (check_delim_after_heredoc(data))
			return (1);
		data = data->next;
	}
	return (0);
}

int	is_unclosed_quotes(char *args)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i] == '\'')
			count += 1;
		if (count == 2)
			count = 0;
		i++;
	}
	if (count != 0)
		return (1);
	else
		return (0);

}

int	main(int ac, char **av, char **env)
{
	t_list *list;
	t_data	*data;
	t_global global;
	char *args;
	signal_handlers(global);
	while (1)
	{
		data = malloc(sizeof(t_data));
		list = malloc(sizeof(t_list));
		if (!list ||!data)
			return (0);
		list->begin = NULL;
		list->end = NULL;
		args = readline("Minishell > ");
		if (!args)
		{
			write(1, "exit\n", 5);
			break;
		}
		add_history(args);
		initialisation(data, args, env);
		global.index++;
		get_word(list, args, data, global);
		get_type(data, list);
		get_file(list);
		if (is_error_2(data, list))
		{
			free_list(list);
			signal_handlers(global);
			continue ;
		}
		get_args_cmd(data, list);
		data = list->begin;
		while (data)
		{
			if (ft_strcmp(data->type, "CMD") == 0)
			{
				exec(list, env, global);
				break;
			}
			data = data->next;
		}
		if (!data)
			print_list(list, args);
		rl_redisplay();
		free_list(list);
		signal_handlers(global);
	}
	return (0);
}