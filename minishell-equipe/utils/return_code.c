/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:44:03 by hmimouni          #+#    #+#             */
/*   Updated: 2025/08/04 17:12:42 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_get_exit_status(int exit_code)
{
	static int	exit_status;

	if (exit_code == -1)
		return (exit_status);
	exit_status = exit_code;
	return (0);
}

void	print_splash_screen(void)
{
	printf("\033[38;5;129m\n");
	printf("%s\n",
		"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ");
	printf("%s\n",
		"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     ");
	printf("%s\n",
		"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     ");
	printf("%s\n",
		"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     ");
	printf("%s\n",
		"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗");
	printf("%s\n",
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝");
	printf("\033[0m\n");
}

void	test_builtins_child(t_data *data, t_list_env *envp, t_list *list)
{
	if (ft_strcmp(data->word, "echo") == 0)
		ft_echo(data->args);
	else if (ft_strcmp(data->word, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->word, "env") == 0)
		ft_env(envp, data);
	close(data->original_stdout);
	close(list->begin->saved_stdin);
	ft_close_all_pipes(list->begin->pipefd, data, list);
	free_env_list(envp);
	ft_malloc(-1);
	exit(0);
}

void	test_builtins_parents(t_data *data, t_list_env *env, t_list *list)
{
	close(data->saved_stdin);
	if (ft_strcmp(data->word, "exit") == 0)
	{
		ft_close_all_pipes(list->begin->pipefd, data, list);
		ft_exit(data->args);
	}
	else if (ft_strcmp(data->word, "export") == 0)
		ft_export(env, data->args);
	else if (ft_strcmp(data->word, "unset") == 0)
		ft_unset(env, data->args);
	else if (ft_strcmp(data->word, "cd") == 0)
		ft_cd(data->args, env);
	(void)data;
	(void)env;
}
