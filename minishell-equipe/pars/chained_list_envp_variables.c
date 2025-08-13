/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_envp_variables.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:50:25 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/23 14:50:25 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_value(char *str)
{
	char	*envp_value;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	envp_value = malloc(sizeof(char) * (len + 1));
	if (!envp_value)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	i++;
	while (str[i])
	{
		envp_value[j] = str[i];
		i++;
		j++;
	}
	envp_value[j] = '\0';
	return (envp_value);
}

void	envp_value(t_list_envp *envp_list, char **envp)
{
	t_envp	*data;
	int		i;

	data = envp_list->begin;
	i = 0;
	while (data)
	{
		data->value = ft_value(envp[i]);
		i++;
		data = data->next;
	}
}

void	node_creation_envp_variables(t_list_envp *envp_list, char *str)
{
	t_envp	*data;

	data = malloc(sizeof(t_envp));
	if (!data)
		return ;
	ft_memset(data, 0, sizeof(t_envp));
	data->key = ft_strdup(str);
	data->next = NULL;
	data->back = NULL;
	if (envp_list->end == NULL)
	{
		envp_list->begin = data;
		envp_list->end = data;
	}
	else
	{
		envp_list->end->next = data;
		data->back = envp_list->end;
		envp_list->end = data;
	}
}

void	get_envp_key(char **envp, t_list_envp *envp_list)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		str = malloc(sizeof(char) * (len + 1));
		if (!str)
			return ;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
		{
			str[j] = envp[i][j];
			j++;
		}
		str[j] = '\0';
		node_creation_envp_variables(envp_list, str);
		free(str);
		i++;
	}
}
