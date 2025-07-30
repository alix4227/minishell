/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:10:08 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/21 22:12:34 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_and_remove(t_list_env *envp, char *key)
{
	t_env	*tmp;

	tmp = envp->begin;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			if (tmp->back)
				tmp->back->next = tmp->next;
			else
				envp->begin = tmp->next;
			if (tmp->next)
				tmp->next->back = tmp->back;
			else
				envp->end = tmp->back;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_list_env *envp, char **args)
{
	int	i;

	i = 1;
	if (!args[i] || !args)
		return ;
	while (args[i])
	{
		find_and_remove(envp, args[i]);
		i++;
	}
}
