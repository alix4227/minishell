/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:41:42 by hmimouni          #+#    #+#             */
/*   Updated: 2025/08/04 19:14:14 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_env(char *expand, t_list_env *env)
{
	char	*out;
	t_env	*tmp;

	tmp = env->begin;
	while (tmp)
	{
		if (ft_strcmp(expand, tmp->key) == 0)
		{
			out = tmp->value;
			return (out);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	exit_clean(int exit_code)
{
	ft_malloc(-1);
	free_env_list(set_get_env(NULL));
	exit(exit_code);
}

t_list_env	*set_get_env(t_list_env *env)
{
	static t_list_env	*saved_envp;

	if (env == NULL)
		return (saved_envp);
	saved_envp = env;
	return (NULL);
}

void	handle_signel(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_malloc(-1);
		free_env_list(set_get_env(NULL));
	}
	exit(130);
}

t_data	*find_next_heredoc(t_data *current)
{
	while (current)
	{
		if (ft_strcmp(current->type, "HERE_DOC") == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
