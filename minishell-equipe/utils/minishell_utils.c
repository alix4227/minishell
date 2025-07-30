/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:51:59 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:51:59 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	ft_strchr(char *left_char, char c)
{
	int	i;

	i = 0;
	while (left_char[i] != '\0')
	{
		if (left_char[i] == c)
		{
			i++;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strcat(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str1;
	int		len1;
	int		len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str1 = ft_malloc((len1 + len2 + 1) * sizeof(char));
	if (!str1 || !s1 || !s2)
		exit_clean(1);
	while (s1[i] != '\0')
	{
		str1[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str1[i++] = s2[j++];
	str1[i] = '\0';
	return (str1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strcat;

	strcat = ft_strcat(s1, s2);
	return (strcat);
}

int	ft_strlen(char const *args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}
