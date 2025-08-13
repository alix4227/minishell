/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:32:34 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/25 15:32:34 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_exec(t_list *list, char *args, t_list_env *env_list)
// {
// 	t_data	*data;
// 	int		flag;

// 	flag = 0;
// 	if (!list || !list->begin)
// 	{
// 		print_error(list, args);
// 		return ;
// 	}
// 	data = list->begin;
// 	data->saved_stdin = dup(STDIN_FILENO);
// 	if (data->saved_stdin < 0)
// 	{
// 		perror("dup");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (handle_cmd_execution(data, list, env_list))
// 		return ;
// 	while (data)
// 	{
// 		if (ft_strcmp(data->type, "HERE_DOC") == 0)
// 		{
// 			here_doc(data, env_list);
// 			dup2(list->begin->saved_stdin, STDIN_FILENO);
// 			close(list->begin->saved_stdin);
// 			flag = 1;
// 			break ;
// 		}
// 		data = data->next;
// 	}
// 	if (!flag)
// 		print_error(list, args);
// }

int	tokenisation_and_exec(t_list *list, char *args,
	t_list_env *env_list, char **env)
{
	t_data	*data;

	data = list->begin;
	get_type(data, list, env_list);
	get_file(list);
	if (wrong_token_error(data, list))
		return (0);
	get_args_cmd(data, list);
	initialisation_cmd_numb(data, list);
	if (!last_pipe_not_followed_by_cmd(data, list))
		return (0);
	print_exec(list, args, env_list, env);
	pipe_not_followed_by_cmd(data, list);
	rl_redisplay();
	signal_handlers();
	return (1);
}

void	program_handler(t_list *list, char *args, char **env,
					t_list_env *env_list)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_clean(1);
	ft_memset(data, 0, sizeof(t_data));
	initialisation(data, args, env);
	if (check_args_error(args))
		return ;
	get_word(list, args, data, env_list);
	if (!tokenisation_and_exec(list, args, env_list, env))
	{
		ft_malloc(-1);
		signal_handlers();
		return ;
	}
	ft_malloc(-1);
}

void	main_loop_function(t_list *list, char *args, char **env,
						t_list_env *env_list)
{
	while (1)
	{
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		set_get_env(env_list);
		initialisation_list(&list);
		args = readline("\033[1m\033[38;5;129mMinishell → \033[0m");
		if (!args)
		{
			write(1, "exit\n", 5);
			return ;
		}
		if (!args[0])
		{
			ft_malloc(-1);
			continue ;
		}
		add_history(args);
		program_handler(list, args, env, env_list);
	}
}

int	main(int ac, char **av, char **env)
{
	t_list		*list;
	char		*args;
	t_list_env	*env_list;

	(void)av;
	(void)ac;
	args = NULL;
	list = NULL;
	print_splash_screen();
	signal_handlers();
	initialisation_env_list(&env_list);
	get_env_key(env, env_list);
	env_value(env_list, env);
	main_loop_function(list, args, env, env_list);
	free_env_list(env_list);
	ft_malloc(-1);
	return (0);
}
