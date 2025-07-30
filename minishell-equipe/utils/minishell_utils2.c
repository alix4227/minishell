/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:53:05 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:53:05 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == ' ' || c == '|')
		return (1);
	return (0);
}

int	is_operator3(char c)
{
	if (c == '>' || c == '<' || c == ';' || c == '|')
		return (1);
	return (0);
}

int	ft_strlen_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data && ft_strcmp(data->word, "|") != 0)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
			i++;
		if (ft_strcmp(data->type, "ARG") == 0)
			i++;
		data = data->next;
	}
	return (i);
}

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;
	char	ch;
	char	*s;

	s = str;
	ch = c;
	i = 0;
	while (i < len)
	{
		s[i] = ch;
		i++;
	}
	return (str);
}

char	*ft_realloc(char *expanded, char *retour, t_data *data)
{
	int		length;
	int		i;
	char	*str;
	int		k;

	length = ft_strlen(retour) + ft_strlen(expanded);
	str = ft_malloc(sizeof(char) * (length + 2));
	k = 0;
	if (!str)
		exit_clean(1);
	i = 0;
	while (retour[i])
	{
		str[i] = retour[i];
		i++;
	}
	while (expanded && expanded[k])
		str[i++] = expanded[k++];
	str[i] = '\0';
	data->j = i;
	return (str);
}
