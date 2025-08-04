/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:54:54 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:54:54 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_pars(t_list *list, t_data *data, int *is_quote)
{
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, data->retour, is_quote);
		data->j = 0;
	}
	data->i++;
}

void	operator_pars(t_list *list, t_data *data, char *args, int *is_quote)
{
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, data->retour, is_quote);
		data->j = 0;
	}
	if (args[data->i] == '>' && args[data->i + 1] == '>')
	{
		node_creation(list, ">>", is_quote);
		data->i += 2;
	}
	else if (args[data->i] == '<' && args[data->i + 1] == '<')
	{
		node_creation(list, "<<", is_quote);
		data->i += 2;
	}
	else
	{
		data->retour[0] = args[data->i++];
		data->retour[1] = '\0';
		node_creation(list, data->retour, is_quote);
	}
}

void	single_quote_pars(t_data *data, char *args, int *is_quote)
{
	data->i++;
	*is_quote = 1;
	while (args[data->i] && args[data->i] != '\'')
		data->retour[data->j++] = args[data->i++];
	if (args[data->i == 1] == '\'')
		data->retour[data->j++] = ' ';
	if (args[data->i] == '\'')
		data->i++;
	else
		return ;
}

void	double_quotes_pars(t_data *data, char *args,
	t_list_env *env, int *is_quote)
{
	data->i++;
	*is_quote = 1;
	while (args[data->i] && args[data->i] != '"')
	{
		if (args[data->i] == '$')
			double_quotes_expansion(data, args, env);
		else
			data->retour[data->j++] = args[data->i++];
	}
	// if (args[data->i == 1] == '"')
	// 	data->retour[data->j++] = ' ';
	if (args[data->i] == '"')
		data->i++;
	else
		return ;
}

int	check_args_error(char *args)
{
	if (is_unclosed_quotes(args))
	{
		ft_malloc(-1);
		signal_handlers();
		set_get_exit_status(0);
		return (1);
	}
	if (parse_error_operators(args))
	{
		ft_malloc(-1);
		signal_handlers();
		set_get_exit_status(0);
		return (1);
	}
	return (0);
}
