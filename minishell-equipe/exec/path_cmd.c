/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/29 18:36:50 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/29 18:36:50 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path_cmd(char *word)
{
	struct stat	check;

	if (access(word, X_OK) == 0)
	{
		if (stat(word, &check) == 0)
		{
			if (S_ISREG(check.st_mode))
				return (1);
		}
	}
	return (0);
}

char	*build_path(char *cmd, char *word)
{
	char	*slash;
	char	*string;

	slash = ft_strjoin(cmd, "/");
	string = ft_strjoin(slash, word);
	return (string);
}

// int	build_check_path_cmd(char *word, t_data *data, int i, int j,
// 		t_list_env *env)
// {
// 	char	*str;
// 	char	cmd[256];
// 	char	*path;
// 	t_env	*current;

// 	path = NULL;
// 	current = env->begin;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, "PATH") == 0)
// 		{
// 			path = current->value;
// 			break ;
// 		}
// 		else
// 			current = current->next;
// 	}
// 	if (!path)
// 		return (1);
// 	while (path[i])
// 	{
// 		j = 0;
// 		while (path[i] && path[i] != ':')
// 			cmd[j++] = path[i++];
// 		cmd[j] = '\0';
// 		str = build_path(cmd, word);
// 		if (check_path_cmd(str))
// 		{
// 			free(data->word);
// 			data->word = str;
// 			return (1);
// 		}
// 		free(str);
// 		i++;
// 	}
// 	return (0);
// }

int	search_cmd_in_path(char *path, char *word, t_data *data)
{
	char	cmd[256];
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (path[i])
	{
		j = 0;
		while (path[i] && path[i] != ':')
			cmd[j++] = path[i++];
		cmd[j] = '\0';
		str = build_path(cmd, word);
		if (check_path_cmd(str))
		{
			data->word = str;
			return (1);
		}
		if (path[i])
			i++;
	}
	return (0);
}

int	build_check_path_cmd(char *word, t_data *data, t_list_env *env)
{
	t_env	*current;
	char	*path;

	current = env->begin;
	path = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
		{
			path = current->value;
			break ;
		}
		current = current->next;
	}
	if (!path)
		return (1);
	return (search_cmd_in_path(path, word, data));
}

int	is_cmd(char *word, t_data *data, t_list_env *env)
{
	if (data->back && is_chevrons(data))
		return (0);
	if (built_cmd_parent(word))
		return (1);
	if (built_cmd_child(word))
		return (1);
	if (check_path_cmd(word))
		return (1);
	if (build_check_path_cmd(word, data, env))
		return (1);
	return (0);
}
