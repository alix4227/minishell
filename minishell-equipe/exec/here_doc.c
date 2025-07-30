/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:28 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/29 14:57:42 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// int	here_doc(t_data *data, t_list_env *env)
// {
// 	int		fd;
// 	pid_t	pid;
// 	int		status;
// 	char *line;

// 	line = NULL;
// 	if (!data || !data->next)
// 		return (0);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0666);
// 		if (fd < 0)
// 			exit(1);
// 		while ((line = readline("\033[1m\033[31mheredoc → \033[0m")) != NULL
// 			&& ft_strcmp(data->next->word, line) != 0)
// 		{
// 			line = expand_line(line, env);
// 			write(fd, line, ft_strlen(line));
// 			write(fd, "\n", 1);
// 			free(line);
// 		}
// 		free(line);
// 		close(fd);
// 		exit (0);
// 	}
// 	else if (pid > 0)
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		waitpid(pid, &status, 0);
// 		signal(SIGINT, SIG_DFL);
// 		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 		{
// 			unlink("here_doc");
// 			write(1, "\n", 1);
// 			return (0);
// 		}
// 		fd = open("here_doc", O_RDONLY);
// 		if (fd < 0)
// 			return (0);
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 		unlink("here_doc");
// 	}
// 	return (1);
// }

int	handle_heredoc_parent(int *status)
{
	int	fd;

	signal(SIGINT, SIG_IGN);
	waitpid(-1, status, 0);
	signal(SIGINT, SIG_DFL);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		unlink("here_doc");
		write(1, "\n", 1);
		return (0);
	}
	fd = open("here_doc", O_RDONLY);
	if (fd < 0)
		return (0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("here_doc");
	return (1);
}

t_list_env	*set_get_env(t_list_env *env)
{
	static t_list_env	*saved_envp;

	if (env == NULL)
		return (saved_envp);
	saved_envp = env;
	return (NULL);
}

void	handle_signel(int sig)
{
	if (sig == SIGINT)
	{
		ft_malloc(-1);
		free_env_list(set_get_env(NULL));
	}
	exit(130);
}

void	handle_heredoc_child(t_data *data, t_list_env *env)
{
	int		fd;
	char	*line;

	signal(SIGINT, handle_signel);
	fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_malloc(-1);
		free_env_list(env);
		exit(1);
	}
	while (1)
	{
		line = readline("\033[1m\033[31mheredoc → \033[0m");
		if (!line || ft_strcmp(data->next->word, line) == 0)
			break ;
		process_heredoc_line(fd, line, env);
	}
	close(fd);
	close(data->saved_stdin);
	ft_malloc(-1);
	free_env_list(env);
	exit(0);
}

int	here_doc(t_data *data, t_list_env *env)
{
	pid_t	pid;
	int		status;

	if (!data || !data->next)
		return (0);
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(data, env);
	else if (pid > 0)
		return (handle_heredoc_parent(&status));
	return (0);
}
