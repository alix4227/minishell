/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:59:04 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:59:04 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_first_cmd(int **pipefd, int i)
{
	dup2(pipefd[i][1], STDOUT_FILENO);
	close(pipefd[i][1]);
}

void	ft_middle_cmd(int **pipefd, int i)
{
	dup2(pipefd[i - 1][0], STDIN_FILENO);
	dup2(pipefd[i][1], STDOUT_FILENO);
	close(pipefd[i][1]);
	close(pipefd[i - 1][0]);
}

void	ft_last_cmd(int **pipefd, int i)
{
	dup2(pipefd[i - 1][0], STDIN_FILENO);
	close(pipefd[i - 1][0]);
}

void	ft_close_all_pipes(int **pipefd, t_data *data, t_list *list)
{
	int	i;
	int	j;

	i = 0;
	data = list->begin;
	j = get_cmd_nb(data, list);
	while (i < (j - 1))
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

void	free_pipes_and_pid(int cmds_numb, t_list *list, pid_t *pid)
{
	int	i;

	i = 0;
	if (cmds_numb > 1)
	{
		while (i < cmds_numb - 1)
			free(list->begin->pipefd[i++]);
		free(list->begin->pipefd);
	}
	free(pid);
}
