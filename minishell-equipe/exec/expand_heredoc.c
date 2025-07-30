/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:02:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/29 13:18:23 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char c)
{
	char	*str;

	str = ft_malloc(2);
	if (!str)
		exit_clean(1);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*append_str(char *base, char *to_add)
{
	char	*new;

	new = ft_strjoin(base, to_add);
	return (new);
}

char	*check_dollar(char *line, int *i, t_list_env *env)
{
	char	*key;
	char	*out;
	int		start;

	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(set_get_exit_status(-1)));
	}
	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	key = ft_substr(line, start, *i - start);
	out = search_in_env(key, env);
	if (!out)
		return (ft_gc_strdup(""));
	return (ft_gc_strdup(out));
}

char	*expand_line(char *line, t_list_env *env)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_gc_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			tmp = check_dollar(line, &i, env);
		else
			tmp = append_char(line[i++]);
		result = append_str(result, tmp);
	}
	return (result);
}

// char	*expand_line(char *line, t_list_env *env)
// {
// 	int		i;
// 	int		j;
// 	char	*key;
// 	char	*expanded;
// 	int		start;
// 	int		len;
// 	char	*out;
// 	int exit_code;

// 	i = 0;
// 	j = 0;

// 	len = ft_strlen(line);
// 	expanded = ft_calloc(1, sizeof(char) * (len + 1));
// 	if (!expanded)
// 	return (NULL);
// 	expanded[len] = '\0';
// 	while (line[i])
// 	{
// 		if (line[i] == '$')
// 		{
// 			i++;
// 			if(line[i] == '?')
// 			{
// 				exit_code = set_get_exit_status(-1);
// 				expanded = ft_realloc2(ft_itoa(exit_code), expanded);
// 				j += ft_strlen(ft_itoa(exit_code));
// 				i++;
// 				continue ;
// 			}
// 			start = i;
// 			while (ft_isalnum(line[i]))
// 				i++;
// 			key = ft_substr(line, start, i - start);
// 			out = search_in_env(key, env);
// 			if (out)
// 			{
// 				expanded = ft_realloc2(out, expanded);
// 				j += ft_strlen(out);
// 			}
// 			free(key);
// 		}
// 		else
// 		{
// 			expanded[j] = line[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	return (expanded);
// }
