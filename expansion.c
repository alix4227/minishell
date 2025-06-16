# include "minishell.h"

char	*get_var_name(char *retour)
{
	int		i;
	int		j;
	char	*str;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(retour);
	str = malloc(sizeof(char) * (len + 1));
	while (retour[i] != '$')
		i++;
	i++;
	while (retour[i] && retour[i] != ' ' && retour[i] != '\'')
	{
		str[j] = retour[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_expand(char *retour)
{
	char	*env_value;
	char	*var;
	int		i;
	int		j;
	int len;

	len = ft_strlen(retour);
	i = 0;
	j = 0;
	var =  get_var_name(retour);
	if (!var[0])
		return(ft_strdup("$"));
	else
		env_value = ft_strdup(getenv(var));
	return (env_value);
}

void	expansion(t_data *data, char *args)
{
	int		k;
	char	*var;
	int		len;
	char	*expand;

	k = 0;
	len = ft_strlen(args);
	var = malloc(sizeof(char) * (len + 1));
	expand = ft_strdup("");
	var[k++] = '$';
	while (args[data->i] && !is_operator(args[data->i]) && !is_quote(args[data->i])
		&& args[data->i] != '$')
		var[k++] = args[data->i++];
	var[k] = '\0';
	expand = get_expand(var);
	data->retour[data->j] = '\0';
	data->retour = ft_realloc(expand, data->retour, data);
	free(var);
}

void	double_quotes_expansion(t_data *data, char *args)
{
	char	*expanded;
	char	*temp;
	int		k;
	int		len;

	expanded = ft_strdup("");
	len = ft_strlen(args);
	temp = malloc(sizeof(char) * (len + 1));
	data->i++;
	k = 0;
	temp[k++] = '$';
	while (args[data->i] && !is_quote(args[data->i]) && args[data->i] != '$' && args[data->i] != ' ')
		temp[k++] = args[data->i++];
	temp[k] = '\0';
	expanded = get_expand(temp);
	data->retour[data->j] = '\0';
	data->retour = ft_realloc(expanded, data->retour, data);
	free(temp);
}