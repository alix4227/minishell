/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:50:12 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/29 23:39:05 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_value(t_list_env *envp, char *key)
{
	char	cwd[1024];
	char	*new_value;
	t_env	*current;

	current = envp->begin;
	while (current != envp->end)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			getcwd(cwd, sizeof(cwd));
			new_value = ft_strdup(cwd);
			if (!new_value)
			{
				perror("cd");
				return ;
			}
			if (current->value)
				free(current->value);
			current->value = new_value;
			return ;
		}
		else
			current = current->next;
	}
}

void	ft_cd(char **args, t_list_env *envp)
{
	if (args[1] == NULL)
		return ;
	pwd_value(envp, "OLDPWD");
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		set_get_exit_status(1);
		return ;
	}
	pwd_value(envp, "PWD");
}
