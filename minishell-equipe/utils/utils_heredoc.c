/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:41:55 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/29 13:28:59 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

int	get_allocation(char const *s, int start, int len)
{
	if (start >= ft_strlen(s))
		return (0);
	if (len < ft_strlen(s + start))
		return (len);
	return (ft_strlen(s + start));
}

void	*ft_calloc(int nmemb, int size)
{
	void	*out;

	out = ft_malloc(nmemb * size);
	if (!out)
		exit_clean(1);
	ft_bzero(out, nmemb * size);
	return (out);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*out;
	int		i;

	i = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	out = ft_calloc(get_allocation(s, start, len) + 1, sizeof(char));
	if (!out)
		return (NULL);
	if (start >= ft_strlen(s))
		return (out);
	while (i < len && s[i + start])
	{
		out[i] = s[i + start];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_realloc2(char *expanded, char *retour)
{
	int		length;
	int		i;
	char	*str;
	int		k;

	length = ft_strlen(retour) + ft_strlen(expanded);
	str = ft_malloc(sizeof(char) * (length + 2));
	if (!str)
		exit_clean(1);
	k = 0;
	i = 0;
	while (retour[i])
	{
		str[i] = retour[i];
		i++;
	}
	while (expanded && expanded[k])
		str[i++] = expanded[k++];
	str[i] = '\0';
	free(retour);
	return (str);
}
