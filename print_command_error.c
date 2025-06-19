/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:19:22 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:19:22 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_error(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((args[0] == '!' || args[0] == ':') && args[1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	print_error(t_list *list, char *args)
{
	t_data	*data;
	int		i;
	int		j;

	data = list->begin;
	if (!list->begin || is_error(args) || is_unclosed_quotes(args))
	{
		g_r_code = 0;
		return ;
	}
	printf("bash:%s: command not found", data->word);
	g_r_code = 127;
	printf("\n");
}