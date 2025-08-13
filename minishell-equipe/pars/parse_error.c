/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:04:30 by acrusoe           #+#    #+#             */
/*   Updated: 2025/08/04 18:28:00 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_after(char *args, int *i)
{
	if (check_after_operator(args, *i + 2))
	{
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	(*i)++;
	return (0);
}

int	is_double_operator(const char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (1);
	else if ((s[0] == '<' && s[1] == '<'))
		return (1);
	else if ((s[0] == '<' && s[1] == '>'))
		return (1);
	return (0);
}

int	is_redirs(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	parse_error_operators(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '"' || args[i] == '\'')
			i = skip_quotes(args, i, args[i]);
		else if (is_double_operator(&args[i]))
		{
			if (check_after(args, &i))
				return (1);
		}
		else if (is_redirs(args[i]))
		{
			if (check_after_operator(args, i + 1))
			{
				printf("bash: syntax error near unexpected token\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
