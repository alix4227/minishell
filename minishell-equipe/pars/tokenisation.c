/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:23:45 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:23:45 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_type(t_data *data, int *cmd_nb, t_list_env *env)
{
	if (*cmd_nb == 0 && is_cmd(data->word, data, env) == 1)
	{
		(*cmd_nb)++;
		return ("CMD");
	}
	else if (!data->flag && ft_strcmp(data->word, ">") == 0)
		return ("REDIR_OUT");
	else if (!data->flag && ft_strcmp(data->word, ">>") == 0)
		return ("REDIR_OUT_APPEND");
	else if (!data->flag && ft_strcmp(data->word, "<") == 0)
		return ("REDIR_IN");
	else if (!data->flag && ft_strcmp(data->word, "<<") == 0)
		return ("HERE_DOC");
	else if (!data->flag && ft_strcmp(data->word, "|") == 0)
	{
		*cmd_nb = 0;
		return ("PIPE");
	}
	else
		return ("ARG");
}

void	get_type(t_data *data, t_list *list, t_list_env *env)
{
	int	cmd_nb;

	cmd_nb = 0;
	data = list->begin;
	while (data)
	{
		data->type = get_token_type(data, &cmd_nb, env);
		data = data->next;
	}
}

int	is_unclosed_quotes(char *args)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (args[i])
	{
		if (args[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
		}
		else if (args[i] == '\"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
		}
		i++;
	}
	if (in_single_quote || in_double_quote)
		return (1);
	return (0);
}
