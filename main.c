# include "minishell.h"
int	g_r_code;
void	print_list(t_list *list)
{
	t_data *data;
	int	i;
	int j;

	data = list->begin;
	// while (data)
	// {
	// 	i = 0;
	// 	if (ft_strcmp(data->type, "CMD") == 0)
	// 	{
	// 		while (data->args[i] != NULL)
	// 		{
	// 			j = 0;
	// 			while (data->args[i][j])
	// 			{
	// 				printf("%c", data->args[i][j]);
	// 				j++;
	// 			}
	// 			printf("\n");
	// 			i++;
	// 		}
	// 	}
	// 	data = data->next;
	// }
	// while (data)
	// {
		// printf("%s\n", data->type);
		// printf("%d\n", ind);
		printf("bash: %s: command not found", data->word);
		g_r_code = 127;
		// data = data->next;
	// }
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
		else if (ft_strcmp(data->word, " ") == 0)
			data->type = "SPACE";
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
		get_args_cmd(data, list);
		get_file(list);
		// print_list(list);
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
			print_list(list);
		rl_redisplay();
		free_list(list);
	}
	return (0);
}