/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:28:44 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/29 13:33:21 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_gc_strdup(char *s1)
{
	char	*str;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = ft_malloc(len + 1);
	if (!str)
		exit_clean(1);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	gc_add_front(t_gc **gc, t_gc *node)
{
	t_gc	*temp;

	if (!(*gc))
	{
		*gc = node;
		return ;
	}
	temp = *gc;
	node->next = temp;
	*gc = node;
}

t_gc	*new_gc_node(void *ptdr)
{
	t_gc	*node;

	node = malloc(sizeof(t_gc));
	if (!node)
		return (NULL);
	node->ptdr = ptdr;
	node->next = NULL;
	return (node);
}

void	free_gc(t_gc *gc)
{
	t_gc	*temp;

	while (gc)
	{
		if (gc->ptdr)
		{
			free(gc->ptdr);
			gc->ptdr = NULL;
		}
		temp = gc->next;
		if (gc)
			free(gc);
		gc = temp;
	}
}

void	*ft_malloc(long long size)
{
	static t_gc	*gc = NULL;
	void		*ptdr;
	t_gc		*node;

	if (size == -1)
	{
		free_gc(gc);
		gc = NULL;
		return (NULL);
	}
	ptdr = malloc(size);
	if (!ptdr)
		return (NULL);
	node = new_gc_node(ptdr);
	if (!node)
		return (free(ptdr), NULL);
	gc_add_front(&gc, node);
	return (ptdr);
}
