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

void	return_code(t_data *data, char *args, t_global global)
{
	int		i;
	char	*code;

	i = 0;
	if (global.index == 1)
		data->retour[data->j++] = '0';
	else
	{
		code = ft_itoa(g_r_code);
		while (code[i])
			data->retour[data->j++] = code[i++];
		free(code);
	}
}