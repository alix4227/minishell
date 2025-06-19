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

void	get_word(t_list *list, char *args, t_data *data, t_global global)
{
	while (args[data->i] == ' ')
		data->i++;
	while (args[data->i])
	{
		if (args[data->i] == ' ')
			space_pars(list, data);
		else if (args[data->i] == '"')
			double_quotes_pars(data, args);
		else if (args[data->i] == '\'')
			single_quote_pars(data, args);
		else if (is_operator(args[data->i]))
			operator_pars(list, data, args);
		else if (args[data->i] == '$')
			dollar_pars(data, args, global);
		else
			data->retour[data->j++] = args[data->i++];
	}
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, ft_strdup(data->retour));
	}
	free(data->retour);
}

void	node_creation(t_list *list, char *retour)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit (1);
	ft_memset(data, 0, sizeof(t_data));
	if (retour[0] != '\0')
		data->word = ft_strdup(retour);
	else
		data->word = ft_strdup(" ");
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
	data->j = 0;
	data->k = 0;
	data->args = NULL;
	data->len = ft_strlen(args);
	data->retour = malloc(sizeof(char) * (data->len + 1));
}
