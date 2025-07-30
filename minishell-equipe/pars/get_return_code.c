/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_return_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:25:53 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:25:53 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_code(t_data *data, char *args)
{
	int		i;
	char	*code;

	i = 0;
	code = ft_itoa(set_get_exit_status(-1));
	if (!code)
		return ;
	while (code[i])
		data->retour[data->j++] = code[i++];
	(void)args;
}

int	check_delim_after_heredoc(t_data *data)
{
	if (ft_strcmp(data->type, "HEREDOC") == 0)
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
			return (0);
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

void	process_heredoc_line(int fd, char *line, t_list_env *env)
{
	char	*expanded;

	expanded = expand_line(line, env);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(line);
}

int	handle_cmd_execution(t_data *data, t_list *list,
							t_list_env *env_list)
{
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			exec(list, env_list);
			if (data->here_doc_fd >= 0)
				unlink("here_doc");
			data->here_doc_fd = 0;
			dup2(list->begin->saved_stdin, STDIN_FILENO);
			close(list->begin->saved_stdin);
			return (1);
		}
		data = data->next;
	}
	return (0);
}

int	has_heredoc(t_data *data)
{
	if (data->type && !ft_strcmp(data->type, "HERE_DOC"))
		return (1);
	return (0);
}
