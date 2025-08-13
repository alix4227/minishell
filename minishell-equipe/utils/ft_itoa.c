/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:11:04 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 09:11:04 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_char(char number, long i, long nbr, char *str)
{
	while (nbr > 0)
	{
		number = (nbr % 10) + '0';
		str[i] = number;
		i--;
		nbr /= 10;
	}
}

int	ft_length(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n > 0)
	{
		while (n > 0)
		{
			n = n / 10;
			len++;
		}
	}
	if (n < 0)
	{
		len = 1;
		n = -1 * n;
		while (n > 0)
		{
			n = n / 10;
			len++;
		}
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	i;
	long	len;
	long	nbr;
	char	number;

	nbr = n;
	len = ft_length(nbr);
	i = len - 1;
	number = 0;
	str = ft_malloc((len + 1) * sizeof(char));
	if (!str)
		exit_clean(1);
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -1 * nbr;
	}
	ft_char(number, i, nbr, str);
	str[len] = '\0';
	return (str);
}

void	reinitialisation_std(int original_stdout, int original_stdin)
{
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}
