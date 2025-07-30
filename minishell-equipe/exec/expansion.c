/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:11:45 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 09:11:45 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *retour)
{
	int		i;
	int		j;
	char	*str;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(retour);
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		exit_clean(1);
	while (retour[i] != '$')
		i++;
	i++;
	while (retour[i] && retour[i] != ' ' && retour[i] != '\'')
	{
		str[j] = retour[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_expand(char *retour, t_list_env *env)
{
	char	*env_value;
	char	*var;

	var = get_var_name(retour);
	if (!var[0])
	{
		return ("$");
	}
	else
		env_value = search_in_env(var, env);
	return (env_value);
}

void	expansion(t_data *data, char *args, t_list_env *env)
{
	int		k;
	char	*var;
	int		len;
	char	*expand;

	k = 0;
	len = ft_strlen(args);
	var = ft_malloc(sizeof(char) * (len + 1));
	if (!var)
		exit_clean(1);
	var[k++] = '$';
	while (args[data->i]
		&& !is_operator(args[data->i])
		&& !is_quote(args[data->i])
		&& args[data->i] != '$')
		var[k++] = args[data->i++];
	var[k] = '\0';
	expand = get_expand(var, env);
	data->retour[data->j] = '\0';
	data->retour = ft_realloc(expand, data->retour, data);
	if (!data->retour)
		return ;
}

void	double_quotes_expansion(t_data *data, char *args, t_list_env *env)
{
	char	*expanded;
	char	*temp;
	int		k;
	int		len;

	len = ft_strlen(args);
	temp = ft_malloc(sizeof(char) * (len + 1));
	if (!temp)
		exit_clean(1);
	data->i++;
	k = 0;
	temp[k++] = '$';
	temp[k++] = '$';
	while (args[data->i]
		&& !is_quote(args[data->i])
		&& args[data->i] != '$'
		&& args[data->i] != ' ')
		temp[k++] = args[data->i++];
	temp[k] = '\0';
	expanded = get_expand(temp, env);
	data->retour[data->j] = '\0';
	data->retour = ft_realloc(expanded, data->retour, data);
	if (!data->retour)
		return ;
}
