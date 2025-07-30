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
