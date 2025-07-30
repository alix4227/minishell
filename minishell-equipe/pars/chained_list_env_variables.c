/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_env_variables.c                       :+:      :+:    :+:   */
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
	char	*env_value;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	env_value = malloc(sizeof(char) * (len + 1));
	if (!env_value)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	i++;
	while (str[i])
	{
		env_value[j] = str[i];
		i++;
		j++;
	}
	env_value[j] = '\0';
	return (env_value);
}

void	env_value(t_list_env *env_list, char **env)
{
	t_env	*data;
	int		i;

	data = env_list->begin;
	i = 0;
	while (data)
	{
		data->value = ft_value(env[i]);
		i++;
		data = data->next;
	}
}

void	node_creation_env_variables(t_list_env *env_list, char *str)
{
	t_env	*data;

	data = malloc(sizeof(t_env));
	if (!data)
		return ;
	ft_memset(data, 0, sizeof(t_env));
	data->key = ft_strdup(str);
	data->next = NULL;
	data->back = NULL;
	if (env_list->end == NULL)
	{
		env_list->begin = data;
		env_list->end = data;
	}
	else
	{
		env_list->end->next = data;
		data->back = env_list->end;
		env_list->end = data;
	}
}

void	get_env_key(char **env, t_list_env *env_list)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		str = malloc(sizeof(char) * (len + 1));
		if (!str)
			return ;
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			str[j] = env[i][j];
			j++;
		}
		str[j] = '\0';
		node_creation_env_variables(env_list, str);
		free(str);
		i++;
	}
}
