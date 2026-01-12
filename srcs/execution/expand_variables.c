#include "builtins.h"

static char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 1;
	if (ft_strlen(str) == 1 || ! (ft_isalpha(str[1]) || str[1] == '_'))
	{
		name = malloc(sizeof(char) * (1 + 1));
		if (!name)
			return NULL;
		name[0] = '$';
		name[1] = '\0';
		return (name);
// la il y a beoins de changer parce que on veut pas le $ avant, ou alors je le laisse partout
// a juste decider et voir si lui je le setup a juste \0 est ce que c'est la meme chose qu'un NULL ?
// et donc que unemalloc raté
	}
	if (str[i] == '$' || str[i] == '?' || ft_isdigit(str[i]))
	{
		name = malloc(sizeof(char) * (2 + 1));
		if (!name)
			return NULL;
		name[0] = '$';
		name[1] = str[1];
		name[2] = '\0';
		return (name);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 1)
		return (ft_strdup(""));

	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);

	ft_strlcpy(name, str, i + 1);
	return (name);
}

static char	*get_env_value(char *key, t_env *env)
{
	t_env	*tmp;

	if (!key)
		return (NULL);
	if (key[0] == '\0')
		return ("$"); // là on veut un malloc de $
	if (ft_strncmp(key, "?", ft_strlen(key)) == 0)
		return ("a");  // ca devrait etre la variable globale pour exit code
	if (ft_strncmp(key, "$",ft_strlen(key)) == 0)
		return (ft_itoa(getpid()));     // PID du shell

	// Recherche dans la liste
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, &key[1], ft_strlen(key) - 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	get_len_variables(char *str, t_env *env)
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
			var_value = get_env_value(var_name, env);
			if (var_value)
				len += ft_strlen(var_value);
			i += ft_strlen(var_name);
			free(var_name);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len + 1);
}

char *expand_variables(char *str, t_env *env)
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
			var_name = get_var_name(&str[i]);
			var_value = get_env_value(var_name, env);
			if (var_value)
			{
				ft_strlcpy(&result[j], var_value, ft_strlen(var_value) + 1);
				j += ft_strlen(var_value);
			}
			i += ft_strlen(var_name);
			free(var_name);
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return (result);
}
