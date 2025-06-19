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

#include "minishell.h"

void	search_redir(t_data *data)
{
	while (data && ft_strcmp(data->type, "PIPE"))
	{
		if (is_redir_in(data))
			ft_redir_in(data);
		else if (is_redir_out(data))
			ft_redir_out(data);
		else if (is_redir_out_append(data))
			ft_redir_out_append(data);
		data = data->next;
	}
}

void	is_redir_start(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_IN") == 0)
		ft_redir_in(data);
	else if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		ft_redir_out(data);
}