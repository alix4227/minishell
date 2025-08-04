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

// int	search_redir(t_data *data, t_list_env *env)
// {
	
// 	int	fd_in[1000];
// 	int i = 0;

// 	while (data && ft_strcmp(data->type, "PIPE"))
// 	{
// 		if (is_redir_in(data))
// 		{
// 			ft_redir_in(data, &fd_in[i]);
// 			i++;
// 		}
// 		else if (has_heredoc(data))
// 		{
// 			if (!here_doc(data, env, &fd_in[i]))
// 				return (0);
// 			i++;
// 		}
// 		else if (is_redir_out(data))
// 			ft_redir_out(data);
// 		else if (is_redir_out_append(data))
// 			ft_redir_out_append(data);
// 		data = data->next;
// 	}
// 	int j = 0;
// 	while (j < i - 1)
// 	{
// 		close(fd_in[j]);
// 		j++;
// 	}
// 	if (i > 0)
// 	{
// 		dup2(fd_in[i - 1], STDIN_FILENO);
// 		close(fd_in[i - 1]);
// 	}
// 	return (1);
// }

// int	is_redir_start(t_data *data, t_list_env *env, t_list *list)
// {
// 	data = list->begin;
// 	if (ft_strcmp(data->type, "REDIR_IN") == 0)
// 		ft_redir_in(data);
// 	else if (ft_strcmp(data->type, "REDIR_OUT") == 0)
// 		ft_redir_out(data);
// 	else if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
// 		ft_redir_out_append(data);
// 	else if (ft_strcmp(data->type, "HERE_DOC") == 0)
// 	{
// 		if (!here_doc(data, env))
// 			return (0);
// 	}
// 	return (1);
// }

int	search_redir(t_data *data, t_list_env *env)
{
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	while (data && data->back && ft_strcmp(data->back->type, "PIPE") != 0)
	{
		data = data->back;
	}
	while (data && ft_strcmp(data->type, "PIPE")!= 0)
	{
		if (is_redir_in(data))
			ft_redir_in(data);
		else if (has_heredoc(data))
		{
			dup2(original_stdin, STDIN_FILENO);
			if (here_doc(data, env))
				return (1);
		}
		else if (is_redir_out(data))
			ft_redir_out(data);
		else if (is_redir_out_append(data))
			ft_redir_out_append(data);
		data = data->next;
	}
	return (1);
}