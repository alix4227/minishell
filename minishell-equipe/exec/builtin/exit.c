/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:41:33 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/28 23:48:23 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (sign * result);
}

static int	is_overflow(const char *str)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		if ((sign == 1 && res > 2147483647) || (sign == -1 && - res
				< -2147483648))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **args)
{
	long	code;

	printf("exit\n");
	if (!args[1])
		exit_clean(set_get_exit_status(-1));
	if (!is_numeric(args[1]) || is_overflow(args[1]))
	{
		dprintf(2, "exit: %s: numeric argument required\n", args[1]);
		exit_clean(255);
	}
	if (args[2])
	{
		dprintf(2, "exit: too many arguments\n");
		exit_clean(1);
	}
	code = ft_atol(args[1]);
	exit_clean(code);
}
