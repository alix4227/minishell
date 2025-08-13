/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:07:45 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 09:07:45 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_get_exit_status(130);
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		set_get_exit_status(130);
	}
}

int	signal_handlers(void)
{
	struct sigaction	action_int;
	struct sigaction	action_quit;

	action_int = (struct sigaction){};
	action_int.sa_handler = signal_handler;
	sigemptyset(&action_int.sa_mask);
	action_int.sa_flags = 0;
	sigaction(SIGINT, &action_int, NULL);
	action_quit = (struct sigaction){};
	action_quit.sa_handler = signal_handler;
	sigemptyset(&action_quit.sa_mask);
	action_quit.sa_flags = 0;
	sigaction(SIGQUIT, &action_quit, NULL);
	return (0);
}

int	is_whitespaces(char *str, int start)
{
	return (str[start] == ' ' || str[start] == '\t' || str[start] == '\n');
}

int	is_delimiter_before(char *args, t_data *data)
{
	int	i;

	i = data->i;
	while (i >= 0 && args[i] != '"')
		i--;
	i--;
	while (i >= 0 && is_whitespaces(args, i))
		i--;
	if (i > 0 && args[i] == '<' && args[i - 1] == '<')
		return (1);
	return (0);
}

int	is_delimiter_before2(char *args, t_data *data)
{
	int	i;

	i = data->i;
	i--;
	if (i - 1 >= 0)
		i--;
	while (i >= 0 && is_whitespaces(args, i))
		i--;
	if (i > 0 && args[i] == '<' && args[i - 1] == '<')
		return (1);
	return (0);
}
