/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:38:46 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/21 23:00:45 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_chevrons(t_data *data)
{
	if (ft_strcmp(data->back->word, ">") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, ">>") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, "<") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, "<<") == 0)
		return (1);
	return (0);
}

int	built_cmd_child(char *str)
{
	if (strcmp(str, "echo") == 0)
		return (1);
	else if (strcmp(str, "pwd") == 0)
		return (1);
	else if (strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	built_cmd_parent(char *str)
{
	if (strcmp(str, "cd") == 0)
		return (1);
	else if (strcmp(str, "export") == 0)
		return (1);
	else if (strcmp(str, "unset") == 0)
		return (1);
	else if (strcmp(str, "exit") == 0)
		return (1);
	return (0);
}
