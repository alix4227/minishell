/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:04:30 by acrusoe           #+#    #+#             */
/*   Updated: 2025/07/30 09:10:38 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_whitespace(char *str, int start)
{
	while (str[start] && str[start] == ' ')
		start++;
	return (start);
}

int	skip_quotes(char *str, int start, char c)
{
	while (str[start] && str[start] != c)
		start++;
	return (start);
}

int	check_after_operator(char *args, int pos)
{
	pos = skip_whitespace(args, pos);
	return (args[pos] == '\0' || is_operator3(args[pos]));
}

int	check_after(char *args, int *i)
{
	if (check_after_operator(args, *i + 2))
	{
		printf("bash: parse error\n");
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

int	parse_error_operators(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '"' || args[i] == '\'')
		{
			i = skip_quotes(args, i, args[i]);
		}
		if (is_double_operator(&args[i]))
		{
			if (check_after(args, &i))
				return (1);
		}
		else if (is_operator3(args[i]))
		{
			if (check_after_operator(args, i + 1))
			{
				printf("bash: parse error\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
