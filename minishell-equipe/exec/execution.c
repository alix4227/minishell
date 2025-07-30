/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:54:46 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/18 21:54:46 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	exec_main_function(t_data *data, t_list *list, t_list_env *env_list,
// 	pid_t *pid)
// {
// 	while (data && list->begin->ind < list->begin->cmds_numb)
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		if (!is_redir_start(data, env_list))
// 		{
// 			data->heredoc_exit = 1;
// 			return(1);
// 		}
// 		if (ft_strcmp(data->type, "CMD") == 0)
// 		{
// 			if (built_cmd_parent(data->word))
// 			{
// 				test_builtins_parents(data, env_list);
// 				return(1);
// 			}
// 			pid[list->begin->ind] = fork();
// 			if (pid[list->begin->ind] < 0)
// 			{
// 				perror("fork failed");
// 				exit(EXIT_FAILURE);
// 			}
// 			else if (pid[list->begin->ind] == 0)
// 			{
// 				if (!child_process_pipe(data, list, env_list, list->begin->ind))
// 				{
// 					data->heredoc_exit = 1;
// 					break;
// 				}
// 			}
// 			list->begin->ind++;
// 		}
// 		data = data->next;
// 	}
// 	return(0);
// }
int	handle_fork_and_exec(t_data *data, t_list *list,
						t_list_env *env_list, pid_t *pid)
{
	int	index;

	index = list->begin->ind;
	pid[index] = fork();
	if (pid[index] < 0)
	{
		perror("fork failed");
		ft_malloc(-1);
		free_env_list(env_list);
		exit(EXIT_FAILURE);
	}
	else if (pid[index] == 0)
	{
		close(list->begin->saved_stdin);
		if (!child_process_pipe(data, list, env_list, index))
		{
			data->heredoc_exit = 1;
			return (0);
		}
	}
	list->begin->ind++;
	return (1);
}

int	handle_heredoc_failure(t_data *data)
{
	data->heredoc_exit = 1;
	return (1);
}

int	handle_builtin_if_needed(t_data *data, t_list_env *env_list, t_list *list)
{
	if (built_cmd_parent(data->word))
	{
		test_builtins_parents(data, env_list, list);
		return (1);
	}
	return (0);
}

int	exec_main_function(t_data *data, t_list *list,
					t_list_env *env_list, pid_t *pid)
{
	while (data && list->begin->ind < list->begin->cmds_numb)
	{
		signal(SIGINT, SIG_IGN);
		if (!is_redir_start(data, env_list))
			return (handle_heredoc_failure(data));
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			if (handle_builtin_if_needed(data, env_list, list))
				return (1);
			if (!handle_fork_and_exec(data, list, env_list, pid))
				break ;
		}
		data = data->next;
	}
	return (0);
}

void	exec(t_list *list, t_list_env *env_list)
{
	t_data	*data;
	int		cmds_numb;
	pid_t	*pid;

	data = list->begin;
	cmds_numb = get_cmd_nb(data, list);
	pid = ft_malloc(sizeof(pid_t) * cmds_numb);
	if (!pid)
		exit_clean(1);
	pipe_creation(data, cmds_numb);
	if (!data->pipefd && cmds_numb > 1)
	{
		free(pid);
		return ;
	}
	if (exec_main_function(data, list, env_list, pid) == 1)
		return ;
	if (cmds_numb > 1)
		ft_close_all_pipes(list->begin->pipefd, data, list);
	if (!data->heredoc_exit)
		pids_handler(pid, cmds_numb);
}
