/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:41:02 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 09:41:02 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator2(char *word)
{
	char	*operators[] = {"|", ">", "<", ">>", NULL};
	int		i;

	i = 0;
	while (operators[i])
	{
		if (ft_strcmp(word, operators[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	fill_args_cmd(t_data *data, int k)
{
	t_data	*cmd;
	int		len;

	cmd = data;
	len = ft_strlen_cmd(data);
	cmd->args = malloc(sizeof(char *) * (len + 1));
	while (data && !is_operator2(data->word))
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			cmd->args[k] = ft_strdup(data->word);
			k++;
		}
		else if (ft_strcmp(data->type, "ARG") == 0)
		{
			cmd->args[k] = ft_strdup(data->word);
			k++;
		}
		data = data->next;
	}
	cmd->args[k] = NULL;
}

void	get_args_cmd(t_data *data, t_list *list)
{
	int	k;

	k = 0;
	data = list->begin;
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			fill_args_cmd(data, k);
			while (data && !is_operator2(data->word))
				data = data->next;
		}
		else
			data = data->next;
	}
}

int	get_cmd_nb(t_data *data)
{
	int	cmds_numb;

	cmds_numb = 0;
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
			cmds_numb++;
		data = data->next;
	}
	return (cmds_numb);
}
