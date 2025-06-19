/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:38:35 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:38:35 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_r_code;

void	print_exec(t_list *list, t_global global, char *args, char **env)
{
	t_data	*data;

	data = list->begin;
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			exec(list, env, global);
			break ;
		}
		data = data->next;
	}
	if (!data)
		print_error(list, args);
}

int	is_unclosed_quotes(char *args)
{
	int	i;
	int	count;
	int	count2;

	i = 0;
	count = 0;
	count2 = 0;
	while (args[i])
	{
		if (args[i] == '\'')
			count += 1;
		if (args[i] == '\"')
			count2 += 1;
		if (count == 2)
			count = 0;
		if (count2 == 2)
			count2 = 0;
		i++;
	}
	if (count != 0 || count2 != 0)
		return (1);
	return (0);
}

void	tokenisation_and_exec(t_list *list, char *args,
	t_global global, char **env)
{
	t_data	*data;

	data = list->begin;
	get_type(data, list);
	get_file(list);
	if (wrong_token_error(data, list))
	{
		free_list(list);
		signal_handlers(global);
		return ;
	}
	get_args_cmd(data, list);
	print_exec(list, global, args, env);
	rl_redisplay();
	free_list(list);
	signal_handlers(global);
}

void	program_handler(t_list *list, char *args, t_global global, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	initialisation(data, args, env);
	if (is_unclosed_quotes(args))
	{
		free_list(list);
		signal_handlers(global);
		g_r_code = 0;
		return ;
	}
	get_word(list, args, data, global);
	tokenisation_and_exec(list, args, global, env);
}

int	main(int ac, char **av, char **env)
{
	t_list		*list;
	t_global	global;
	char		*args;

	signal_handlers(global);
	while (1)
	{
		list = malloc(sizeof(t_list));
		if (!list)
			return (0);
		list->begin = NULL;
		list->end = NULL;
		args = readline("Minishell > ");
		if (!args)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(args);
		global.index++;
		program_handler(list, args, global, env);
	}
	return (0);
}
