/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:10:04 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:10:04 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_redir(t_data *data, t_list_env *env)
{
	int	original_stdin;
	int	flag;

	flag = 0;
	original_stdin = dup(STDIN_FILENO);
	while (data && data->back && ft_strcmp(data->back->type, "PIPE") != 0)
		data = data->back;
	while (data && ft_strcmp(data->type, "PIPE") != 0)
	{
		if (is_redir_in(data))
			ft_redir_in(data);
		else if (!flag && has_heredoc(data))
		{
			flag = 1;
			dup2(original_stdin, STDIN_FILENO);
			if (!here_doc(data, env))
				exit(130);
		}
		else if (is_redir_out(data))
			ft_redir_out(data);
		else if (is_redir_out_append(data))
			ft_redir_out_append(data);
		data = data->next;
	}
	return (1);
}

int	is_last_heredoc(t_data *data)
{
	t_data	*current;

	current = data->next;
	while (current)
	{
		if (ft_strcmp(current->type, "HERE_DOC") == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

void	ft_redir_out2(t_data *data)
{
	int	fd_outfile;

	if (is_redir_out(data) && data->next
		&& ft_strcmp(data->next->type, "FILE") == 0)
	{
		fd_outfile = open(data->next->word, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd_outfile < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
		close(fd_outfile);
	}
}
