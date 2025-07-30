/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:56 by acrusoe           #+#    #+#             */
/*   Updated: 2025/07/16 15:54:56 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_pipes(int **pipefd, int n)
{
	int	i;

	if (!pipefd)
		return ;
	i = 0;
	while (i < n)
	{
		if (pipefd[i])
			free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

void	pipe_creation(t_data *data, int cmds_numb)
{
	int	i;

	i = 0;
	if (cmds_numb > 1)
	{
		data->pipefd = ft_malloc(sizeof(int *) * (cmds_numb - 1));
		if (!data->pipefd)
			exit_clean(1);
	}
	while (i < (cmds_numb - 1))
	{
		data->pipefd[i] = ft_malloc(sizeof(int) * 2);
		if (!data->pipefd[i])
		{
			ft_free_pipes(data->pipefd, i);
			exit_clean(1);
			return ;
		}
		pipe(data->pipefd[i]);
		i++;
	}
}

void	check_pipes(int i, t_data *data, t_list *list, int cmds_numb)
{
	if (i == 0)
		ft_first_cmd(list->begin->pipefd, i);
	else if (i == cmds_numb - 1)
		ft_last_cmd(list->begin->pipefd, i);
	else
		ft_middle_cmd(list->begin->pipefd, i);
	ft_close_all_pipes(list->begin->pipefd, data, list);
}

int	child_process_pipe(t_data *data, t_list *list,
						t_list_env *env_list, int i)
{
	int	cmds_numb;
	int	redirout;

	cmds_numb = get_cmd_nb(data, list);
	redirout = 0;
	signal(SIGINT, SIG_DFL);
	if (!search_redir(data, env_list, &redirout))
		exit(0);
	if (!redirout && cmds_numb > 1)
		check_pipes(i, data, list, cmds_numb);
	if (built_cmd_child(data->word))
		test_builtins_child(data, env_list, list);
	else
		execve(data->word, data->args, data->env_child_process);
	perror("execve");
	exit(EXIT_FAILURE);
	return (1);
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
		{
			perror("waitpid");
			return ;
		}
		if (k == cmds_numb - 1)
			last_pid_handler(status);
		k++;
	}
}
