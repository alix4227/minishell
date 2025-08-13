/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:28 by hmimouni          #+#    #+#             */
/*   Updated: 2025/08/09 11:28:07 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc_parent(int status)
{
	int	fd;

	signal(SIGINT, SIG_IGN);
	waitpid(-1, &status, 0);
	signal(SIGINT, SIG_DFL);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		unlink("here_doc");
		set_get_exit_status(130);
		return (0);
	}
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 0))
	{
		fd = open("here_doc", O_RDONLY);
		if (fd < 0)
			return (0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink("here_doc");
		set_get_exit_status(0);
	}
	return (1);
}

char	*get_current_delimiter(t_data *data)
{
	if (data && data->next && data->next->word)
		return (data->next->word);
	return (NULL);
}

void	process_single_heredoc(t_data *data, t_list_env *env, int fd)
{
	char	*line;
	char	*expanded;
	char	*current_delimiter;

	current_delimiter = get_current_delimiter(data);
	if (!current_delimiter)
		return ;
	while (1)
	{
		line = readline("\033[1m\033[31mheredoc → \033[0m");
		if (!line)
			read2(data, fd, env);
		expanded = expand_line(line, env);
		if (ft_strcmp(current_delimiter, line) == 0)
		{
			set_get_exit_status(0);
			break ;
		}
		if (fd >= 0)
		{
			write(fd, expanded, ft_strlen(expanded));
			write(fd, "\n", 1);
		}
	}
}

// void	handle_heredoc_child(t_data *data, t_list_env *env)
// {
// 	int		fd;
// 	t_data	*current_heredoc;
// 	t_data	*last_heredoc;

// 	signal(SIGINT, handle_signel);
// 	last_heredoc = NULL;
// 	current_heredoc = data;
// 	fd = -1;
// 	while (current_heredoc)
// 	{
// 		if (ft_strcmp(current_heredoc->type, "HERE_DOC") == 0)
// 			last_heredoc = current_heredoc;
// 		current_heredoc = current_heredoc->next;
// 	}
// 	current_heredoc = data;
// 	while (current_heredoc)
// 	{
// 		if (ft_strcmp(current_heredoc->type, "HERE_DOC") == 0)
// 		{
// 			if (current_heredoc == last_heredoc)
// 			{
// 				fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0666);
// 				if (fd < 0)
// 				{
// 					ft_malloc(-1);
// 					free_env_list(env);
// 					exit(1);
// 				}
// 				process_single_heredoc(current_heredoc, env, fd);
// 				close(fd);
// 			}
// 			else
// 				process_single_heredoc(current_heredoc, env, -1);
// 		}
// 		current_heredoc = current_heredoc->next;
// 	}
// 	close(data->saved_stdin);
// 	ft_malloc(-1);
// 	free_env_list(env);
// 	exit(0);
// }

void	handle_heredoc_child(t_data *data, t_list_env *env)
{
	int		fd;
	t_data	*last_heredoc;

	signal(SIGINT, handle_signel);
	last_heredoc = find_last_heredoc(data);
	fd = process_all_heredocs(data, env, last_heredoc);
	if (fd != -1)
		close(fd);
	cleanup_and_exit(data, env);
}

int	here_doc(t_data *data, t_list_env *env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!data || !data->next)
		return (0);
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(data, env);
	else if (pid > 0)
		return (handle_heredoc_parent(status));
	return (0);
}
