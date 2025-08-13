/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:38:46 by hmimouni          #+#    #+#             */
/*   Updated: 2025/08/08 10:38:45 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_chevrons(t_data *data)
{
	if (ft_strcmp(data->back->word, ">") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, ">>") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, "<") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, "<<") == 0)
		return (1);
	return (0);
}

int	built_cmd_child(char *str)
{
	if (strcmp(str, "echo") == 0)
		return (1);
	else if (strcmp(str, "pwd") == 0)
		return (1);
	else if (strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	built_cmd_parent(char *str)
{
	if (strcmp(str, "cd") == 0)
		return (1);
	else if (strcmp(str, "export") == 0)
		return (1);
	else if (strcmp(str, "unset") == 0)
		return (1);
	else if (strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	last_pid_handler(int status)
{
	if (WIFEXITED(status))
		set_get_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			set_get_exit_status(WTERMSIG(status) + 128);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "\n", 1);
			set_get_exit_status(WTERMSIG(status) + 128);
		}
	}
}

void	pids_handler(pid_t *pid, int cmds_numb)
{
	int	status;
	int	k;

	k = 0;
	while (k < cmds_numb)
	{
		if (waitpid(pid[k], &status, 0) == -1)
			return ;
		if (k == cmds_numb - 1)
			last_pid_handler(status);
		k++;
	}
}
