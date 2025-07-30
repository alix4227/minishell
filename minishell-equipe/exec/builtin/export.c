/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:07:09 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/21 22:11:41 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_existing_env(t_env *existing_node, char *key, char *value)
{
	free(existing_node->value);
	existing_node->value = value;
	free(key);
}

void	export_arg(t_list_env *envp, char *arg)
{
	t_env	*existing_node;
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		dprintf(2, "export: invalid identifier: %s\n", arg);
		return ;
	}
	split_key_value(arg, &key, &value);
	existing_node = env_list_find(envp, key);
	if (existing_node)
		update_existing_env(existing_node, key, value);
	else
		add_new_env(envp, arg, key, value);
}

void	ft_export(t_list_env *envp, char **args)
{
	int	i;

	if (!args || !args[0])
		return ;
	i = 1;
	while (args[i])
	{
		export_arg(envp, args[i]);
		i++;
	}
}
