/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:56:28 by hmimouni          #+#    #+#             */
/*   Updated: 2025/08/08 14:46:17 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*find_last_heredoc(t_data *data)
{
	t_data	*last;

	last = NULL;
	while (data)
	{
		if (ft_strcmp(data->type, "HERE_DOC") == 0)
			last = data;
		data = data->next;
	}
	return (last);
}

void	handle_heredoc_error(t_list_env *env)
{
	ft_malloc(-1);
	free_env_list(env);
	exit(1);
}

int	process_all_heredocs(t_data *data, t_list_env *env, t_data *last_heredoc)
{
	int	fd;

	fd = -1;
	while (data)
	{
		if (ft_strcmp(data->type, "HERE_DOC") == 0)
		{
			if (data == last_heredoc)
			{
				fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0666);
				if (fd < 0)
					handle_heredoc_error(env);
				process_single_heredoc(data, env, fd);
			}
			else
				process_single_heredoc(data, env, -1);
		}
		data = data->next;
	}
	return (fd);
}

void	cleanup_and_exit(t_data *data, t_list_env *env)
{
	close(data->saved_stdin);
	ft_malloc(-1);
	free_env_list(env);
	exit(0);
}

void	read2(t_data *data, int fd, t_list_env *env)
{
	write(2, "warning: here-document delimited by end-of-file\n", 48);
	close(data->saved_stdin);
	close(fd);
	ft_malloc(-1);
	set_get_exit_status(0);
	free_env_list(env);
	exit(0);
}
