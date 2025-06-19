/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:21:37 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:21:37 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args_cmd(t_data *temp, int i)
{
	while (temp->args[i])
	{
		free(temp->args[i]);
		temp->args[i] = NULL;
		i++;
	}
	free(temp->args);
	temp->args = NULL;
}

void	free_list(t_list *list)
{
	t_data	*data;
	t_data	*temp;
	int		i;

	if (!list)
		return ;
	data = list->begin;
	while (data)
	{
		temp = data;
		if (temp->args)
		{
			i = 0;
			free_args_cmd(temp, i);
		}
		data = data->next;
		free(temp->word);
		free(temp);
		temp = NULL;
	}
	list->begin = NULL;
	free(list);
}