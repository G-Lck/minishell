#include "minishell.h"

static char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	if (ft_strlen(str) == 1 || ! (ft_isalpha(str[1]) || str[1] == '_'))
	{
		name = malloc(sizeof(char) * (1));
		if (!name)
			return NULL;
		name[1] = '\0';
		return (name);
// la il y a beoins de changer parce que on veut pas le $ avant, ou alors je le laisse partout
// a juste decider et voir si lui je le setup a juste \0 est ce que c'est la meme chose qu'un NULL ?
// et donc que unemalloc raté
	}
	if (str[1] == '$' || str[1] == '?' || ft_isdigit(str[1]))
	{
		name = malloc(sizeof(char) * (1 + 1));
		if (!name)
			return NULL;
		name[0] = str[1];
		name[1] = '\0';
		return (name);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0)
		return (ft_strdup(""));

	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);

	ft_strlcpy(name, str, i + 1);
	return (name);
}

static char	*get_env_value(char *key, t_list *env)
{
	t_list	*tmp;

	if (!key)
		return (NULL);
	if (key[0] == '\0')
		return ("$"); // là on veut un malloc de $
	if (ft_strcmp(key, "?") == 0)
		return ("a");  // ca devrait etre la variable globale pour exit code
	if (ft_strcmp(key, "$") == 0)
		return (ft_itoa(getpid()));     // PID du shell

	// Recherche dans la liste
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	get_len_variables(char *str, t_list *env)
{
	int		i;
	int		len;
	char	*var_name;
	char	*var_value;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = get_var_name(&str[i]);
			var_value = get_env_value(env, var_name);
			if (var_value)
				len += ft_strlen(var_value);
			i += ft_strlen(var_name) + 1;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len + 1);
}

char *expand_variables(char *str, t_list *env)
{
	int		i;
	int		j;
	char	*result;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 0;
	result = malloc(get_len_variables(str, env));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = get_var_name(&str[i + 1]);
			var_value = get_env_value(env, var_name);
			ft_strlcpy(&result[j], var_value, ft_strlen(var_value));
			j += ft_strlen(var_value);
			i += ft_strlen(var_name) + 1;
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	return (result);
}
