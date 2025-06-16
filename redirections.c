# include "minishell.h"

int	is_redir_in(t_data *data)
{
	while (data)
	{
		if (ft_strcmp(data->type, "REDIR_IN") == 0)
			return (1);
		data = data->next;
	}
	return (0);
}

void	ft_redir_in(t_data *data)
{
	int fd_infile;
	while (data)
	{
		if (ft_strcmp(data->type, "REDIR_IN") == 0)
		{
			while (data)
			{
				if (ft_strcmp(data->type, "FILE") == 0 && data->word != NULL)
				{
					fd_infile = open(data->word, O_RDONLY);
					if (fd_infile < 0)
					{
						perror("open failed");
						exit(EXIT_FAILURE);
					}
					dup2(fd_infile, STDIN_FILENO);
					close(fd_infile);
					break;
				}
				data = data->next;
			}
		}
		data = data->next;
	}
}

int	is_redir_out(t_data *data)
{
	while (data)
	{
		if (ft_strcmp(data->type, "REDIR_OUT") == 0)
			return (1);
		data = data->next;
	}
	return (0);
}


void	ft_redir_out(t_data *data)
{
	int fd_outfile;
	while (data)
	{
		if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		{
			while (data)
			{
				if (ft_strcmp(data->type, "FILE") == 0 && data->word != NULL)
				{
					fd_outfile = open(data->word, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
					if (fd_outfile < 0)
					{
						perror("open failed");
						exit(EXIT_FAILURE);
					}
					dup2(fd_outfile, STDOUT_FILENO);
					close(fd_outfile);
					break;
				}
				data = data->next;
			}
		}
		data = data->next;
	}
}

int	is_redir_out_append(t_data *data)
{
	while (data)
	{
		if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
			return (1);
		data = data->next;
	}
	return (0);
}


void	ft_redir_out_append(t_data *data)
{
	int fd_outfile;
	while (data)
	{
		if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
		{
			while (data)
			{
				if (ft_strcmp(data->type, "FILE") == 0 && data->word != NULL)
				{
					fd_outfile = open(data->word, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
					if (fd_outfile < 0)
					{
						perror("open failed");
						exit(EXIT_FAILURE);
					}
					dup2(fd_outfile, STDOUT_FILENO);
					close(fd_outfile);
					break;
				}
				data = data->next;
			}
		}
		data = data->next;
	}
}

void	search_redir(t_data * data)
{
	while (data && ft_strcmp(data->type, "PIPE"))
	{
		if (is_redir_in(data))
			ft_redir_in(data);
		if (is_redir_out(data))
			ft_redir_out(data);
		if (is_redir_out_append(data))
			ft_redir_out_append(data);
		data = data->next;
	}
}

void	search_redir_start(t_data * data)
{
	while (data && ft_strcmp(data->type, "PIPE"))
	{
		if (is_redir_in(data))
		{
			ft_redir_in(data);
			break;
		}
		else if (is_redir_out(data))
		{
			ft_redir_out(data);
			break;
		}
		data = data->next;
	}
}