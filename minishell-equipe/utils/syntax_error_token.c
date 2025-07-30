/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax error token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:15:33 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:15:33 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_after_redirin(t_data *data)
{
	struct stat	sb;

	if (ft_strcmp(data->type, "REDIR_IN") == 0)
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
		{
			if (stat(data->next->word, &sb) != 0 || !S_ISREG(sb.st_mode))
			{
				printf("bash: No such file or directory \n");
				return (1);
			}
			else if ((access(data->next->word, R_OK) != 0))
			{
				printf("bash: permission denied\n");
				return (1);
			}
			return (0);
		}
	}
	return (0);
}

int	check_file_after_redirout(t_data *data)
{
	if (is_redir_out2(data) || is_redir_out_append(data))
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
			return (0);
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	last_pipe_not_followed_by_cmd(t_data *data)
{
	int	flags;

	flags = 1;
	while (data)
	{
		if (ft_strcmp(data->type, "PIPE") == 0)
		{
			if (!data->next || ft_strcmp(data->next->type, "CMD"))
				flags = 0;
		}
		data = data->next;
	}
	if (flags == 0)
	{
		printf("bash: command not found\n");
		return (0);
	}
	return (1);
}

void	pipe_not_followed_by_cmd(t_data *data)
{
	int	flags;

	flags = 0;
	while (data != NULL)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
			flags = 1;
		if (ft_strcmp(data->type, "PIPE") == 0)
		{
			if (flags == 0)
				printf("bash: command not found\n");
			else
				flags = 0;
		}
		data = data->next;
	}
}

int	wrong_token_error(t_data *data, t_list *list)
{
	if (!list->begin)
		return (0);
	data = list->begin;
	if (ft_strcmp(list->begin->type, "PIPE") == 0)
	{
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	while (data)
	{
		if (check_file_after_redirin(data))
			return (1);
		if (check_file_after_redirout(data))
			return (1);
		else if (check_delim_after_heredoc(data))
			return (1);
		data = data->next;
	}
	return (0);
}
