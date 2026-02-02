/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_env_value(char *key, t_env *env)
{
	t_env	*var;

	if (!key)
		return (NULL);
	if (key[0] == '\0')
		return (ft_strdup("$"));
	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_strdup("0"));// utiliser exit_code du minishell
	if (ft_strncmp(key, "$", 2) == 0)
		return (ft_itoa(getpid()));
	// Recherche dans la liste en utilisant find_env_var
	var = find_env_var(env, &key[1]);
	if (var)
		return (var->value);
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

static int	substitute_variable(char *result, int *j, char *str, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		used;

	var_name = get_var_name(str);
	var_value = get_env_value(var_name, env);
	if (var_value)
	{
		ft_strlcpy(&result[*j], var_value, ft_strlen(var_value) + 1);
		*j += ft_strlen(var_value);
	}
	used = ft_strlen(var_name);
	free(var_name);
	return (used);
}

char	*expand_variables(char *str, t_env *env)
{
	int		in_quotes;
	int		in_dquotes;
	int		i;
	int		j;
	char	*result;

	in_quotes = 0;
	in_dquotes = 0;
	i = 0;
	j = 0;
	result = malloc(get_len_variables(str, env));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && in_quotes == 0)
			in_dquotes = !in_dquotes;
		else if (str[i] == '\'' && in_dquotes == 0)
			in_quotes = !in_quotes;
		if (str[i] == '$' && in_quotes != 1)
			i += substitute_variable(result, &j, &str[i], env);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
