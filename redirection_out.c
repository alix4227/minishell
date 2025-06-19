/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:09:14 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:09:14 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_out(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		return (1);
	return (0);
}

void	ft_redir_out(t_data *data)
{
	int	fd_outfile;

	if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
	{
		fd_outfile = open(data->next->word, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd_outfile < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
}

int	is_redir_out_append(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
		return (1);
	return (0);
}

void	ft_redir_out_append(t_data *data)
{
	int	fd_outfile;

	if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
	{
		fd_outfile = open(data->next->word, O_CREAT | O_WRONLY
				| O_APPEND, S_IRUSR | S_IWUSR);
		if (fd_outfile < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
}