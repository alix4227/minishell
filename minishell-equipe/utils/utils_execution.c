/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:55:57 by hmimouni          #+#    #+#             */
/*   Updated: 2025/08/01 19:03:44 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirections(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		return (1);
	if (ft_strcmp(data->type, "REDIR_IN") == 0)
		return (1);
	if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
		return (1);
	return (0);
}

void	get_file(t_list *list)
{
	t_data	*data;

	data = list->begin;
	while (data)
	{
		if (is_redirections(data))
		{
			if (data->next && ft_strcmp(data->type, "PIPE"))
				data->next->type = "FILE";
		}
		else if (ft_strcmp(data->type, "HERE_DOC") == 0)
		{
			if (data->next)
				data->next->type = "DELIM";
		}
		data = data->next;
	}
}

int	is_cmd_type(t_data *data)
{
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
			return (1);
		data = data->next;
	}
	return (0);
}
