/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:04:41 by hmimouni          #+#    #+#             */
/*   Updated: 2025/08/07 14:52:19 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 1;
	if (!str || !str[0])
		return (0);
	if (!((str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= 'a' && str[0] <= 'z')
			|| str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strndup(char *s, int n)
{
	int		i;
	char	*dup;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && i < n)
		i++;
	dup = ft_malloc(i + 1);
	if (!dup)
		exit_clean(1);
	while (j < i)
	{
		dup[j] = s[j];
		j++;
	}
	dup[i] = '\0';
	return (dup);
}

int	handle_builtin_if_needed(t_data *data, t_list_env *env_list, t_list *list)
{
	if (built_cmd_parent(data->word))
	{
		test_builtins_parents(data, env_list, list);
		return (1);
	}
	return (0);
}
