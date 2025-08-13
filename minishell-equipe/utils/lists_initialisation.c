/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_initialisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:06:24 by acrusoe           #+#    #+#             */
/*   Updated: 2025/07/16 17:06:24 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialisation_env_list(t_list_env **env_list)
{
	*env_list = malloc(sizeof(t_list_env));
	if (!*env_list)
		return ;
	(*env_list)->begin = NULL;
	(*env_list)->end = NULL;
}

void	initialisation_list(t_list **list)
{
	*list = ft_malloc(sizeof(t_list));
	if (!*list)
		exit_clean(1);
	(*list)->begin = NULL;
	(*list)->end = NULL;
}

void	here_doc_without_cmd(t_data	*data, t_list_env *env_list,
	int *flag, t_list *list)
{
	while (data)
	{
		if (ft_strcmp(data->type, "HERE_DOC") == 0)
		{
			here_doc(data, env_list);
			dup2(list->begin->saved_stdin, STDIN_FILENO);
			close(list->begin->saved_stdin);
			*flag = 1;
			break ;
		}
		data = data->next;
	}
}

void	print_exec(t_list *list, char *args, t_list_env *env_list, char **env)
{
	t_data	*data;

	if (!list || !list->begin)
	{
		print_error(list, args);
		return ;
	}
	data = list->begin;
	data->saved_stdin = dup(STDIN_FILENO);
	if (data->saved_stdin < 0)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	if (handle_cmd_execution(data, list, env_list, env))
		return ;
	if (!check_and_handle_here_doc(list, env_list))
		print_error(list, args);
}
