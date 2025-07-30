/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/19 09:41:02 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 09:41:02 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator2(char *word)
{
	int		i;
	char	*operators[6];

	operators[0] = "PIPE";
	operators[1] = "REDIROUT";
	operators[2] = "REDIR_IN";
	operators[3] = "REDIR_OUT_APPEND";
	operators[4] = "HERE_DOC";
	operators[5] = NULL;
	i = 0;
	while (operators[i])
	{
		if (ft_strcmp(word, operators[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ends_with(const char *str, const char *suffix)
{
	size_t	len_str;
	size_t	len_suffix;

	len_str = strlen(str);
	len_suffix = strlen(suffix);
	if (len_str < len_suffix)
		return (0);
	return (strcmp(str + len_str - len_suffix, suffix) == 0);
}

void	fill_args_cmd(t_data *data, int k)
{
	t_data	*cmd;
	int		len;

	cmd = data;
	len = ft_strlen_cmd(data);
	cmd->args = ft_malloc(sizeof(char *) * (len + 2));
	if (!cmd->args)
		exit_clean(1);
	while (data && !is_operator2(data->type))
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			cmd->args[k++] = data->word;
			if (ends_with(data->word, "/grep")
				|| ft_strcmp(data->word, "grep") == 0)
				cmd->args[k++] = ft_gc_strdup("--color=always");
		}
		else if (ft_strcmp(data->type, "ARG") == 0)
			cmd->args[k++] = data->word;
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
			while (data && !is_operator2(data->type))
				data = data->next;
		}
		else
			data = data->next;
	}
}

int	get_cmd_nb(t_data *data, t_list *list)
{
	int	cmds_numb;

	cmds_numb = 0;
	data = list->begin;
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
			cmds_numb++;
		data = data->next;
	}
	return (cmds_numb);
}
