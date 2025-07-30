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

int	search_redir(t_data *data, t_list_env *env, int *redirout)
{
	while (data && ft_strcmp(data->type, "PIPE"))
	{
		if (is_redir_in(data))
			ft_redir_in(data);
		else if (has_heredoc(data))
		{
			if (!here_doc(data, env))
				return (0);
		}
		else if (is_redir_out(data, redirout))
			ft_redir_out(data);
		else if (is_redir_out_append(data))
			ft_redir_out_append(data);
		data = data->next;
	}
	return (1);
}

int	is_redir_start(t_data *data, t_list_env *env)
{
	if (ft_strcmp(data->type, "REDIR_IN") == 0)
		ft_redir_in(data);
	else if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		ft_redir_out(data);
	else if (ft_strcmp(data->type, "HERE_DOC") == 0)
	{
		if (!here_doc(data, env))
			return (0);
	}
	return (1);
}
