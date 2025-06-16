# include "minishell.h"

int	is_cmd(char *word, t_data *data)
{
	char	*path;
	char	*slash;
	char	*str;
	char	cmd[256];
	int		i;
	int		j;
	struct 	stat check;

	path = getenv("PATH");
	i = 0;
	if (access(word, X_OK) == 0)
	{
		if (stat(word, &check) == 0)
		{
			if (S_ISREG(check.st_mode))
				return (1);
		}
	}
	while (path[i])
	{
		j = 0;
		while (path[i] && path[i] != ':')
			cmd[j++] = path[i++];
		cmd[j] = '\0';
		slash = ft_strjoin(cmd, "/");
		str = ft_strjoin(slash, word);
		if (access(str, X_OK) == 0)
		{
			if (stat(str, &check) == 0)
			{
				if (S_ISREG(check.st_mode))
				{
					data->word = ft_strdup(str);
					return (1);
				}
			}
		}
		i++;
	}
	
	return (0);
}