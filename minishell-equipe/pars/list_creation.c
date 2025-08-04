/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:09:49 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 09:09:49 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_word(t_list *list, char *args, t_data *data, t_list_env *env)
{
	int	is_quote;

	is_quote = 0;
	while (args[data->i] == ' ')
		data->i++;
	while (args[data->i])
	{
		if (args[data->i] == ' ')
			space_pars(list, data, &is_quote);
		else if (args[data->i] == '"')
			double_quotes_pars(data, args, env, &is_quote);
		else if (args[data->i] == '\'')
			single_quote_pars(data, args, &is_quote);
		else if (is_operator(args[data->i]))
			operator_pars(list, data, args, &is_quote);
		else if (args[data->i] == '$')
			dollar_pars(data, args, env);
		else if (args[data->i] == '\\' || args[data->i] == ';')
			data->i++;
		else
			data->retour[data->j++] = args[data->i++];
	}
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, data->retour, &is_quote);
	}
}

void	does_word_exist(t_data *data, char *retour, int *is_quote)
{
	if (retour[0] != '\0')
	{
		data->word = ft_gc_strdup(retour);
		if (*is_quote == 1)
		{
			data->flag = 1;
			*is_quote = 0;
		}
	}
	else
		data->word = ft_gc_strdup(" ");
}

void	node_creation(t_list *list, char *retour, int *is_quote)
{
	t_data	*data;

	data = ft_malloc(sizeof(t_data));
	if (!data)
		exit_clean(1);
	ft_memset(data, 0, sizeof(t_data));
	does_word_exist(data, retour, is_quote);
	data->next = NULL;
	data->back = NULL;
	if (list->end == NULL)
	{
		list->begin = data;
		list->end = data;
	}
	else
	{
		list->end->next = data;
		data->back = list->end;
		list->end = data;
	}
}

void	initialisation(t_data *data, char *args, char **env)
{
	data->i = 0;
	data->flag = 0;
	data->is_quote = 0;
	data->ind = 0;
	data->j = 0;
	data->k = 0;
	data->here_doc_fd = 0;
	data->args = NULL;
	data->cmds_numb = 0;
	data->len = ft_strlen(args);
	data->retour = ft_malloc(sizeof(char) * (data->len + 1));
	if (!data->retour)
	{
		ft_malloc(-1);
		free_env_list(set_get_env(NULL));
		exit(1);
	}
	data->env_child_process = env;
}

void	initialisation_cmd_numb(t_data *data, t_list *list)
{
	if (!data)
		return ;
	data->cmds_numb = get_cmd_nb(data, list);
}
