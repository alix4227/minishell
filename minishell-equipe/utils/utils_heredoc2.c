/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:41:42 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/29 13:58:16 by hmimouni         ###   ########.fr       */
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
