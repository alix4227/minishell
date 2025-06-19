/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:00:31 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 09:00:31 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_in(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_IN") == 0)
		return (1);
	return (0);
}

void	ft_redir_in(t_data *data)
{
	int	fd_infile;

	if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
	{
		fd_infile = open(data->next->word, O_CREAT | O_RDONLY);
		if (fd_infile < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
}

