/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance           #+#    #+#             */
/*   Updated: 2026/03/05 23:22:38 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *key, t_minishell *minishell)
{
	t_env	*var;

	if (!key)
		return (NULL);
	if (key[1] == '\0')
		return (ft_strdup("$"));
	if (key[0] == '$')
	{
		if (key[1] == '?' && key[2] == '\0')
			return (ft_itoa(minishell->previous_status));
		if (key[1] == '$')
			return (ft_itoa(getpid()));
		if (ft_isdigit(key[1]))
			return (ft_strdup(""));
		var = find_env_var(minishell->env, &key[1]);
		if (var)
			return (var->value);
		return (NULL);
	}
	var = find_env_var(minishell->env, key);
	if (var)
		return (var->value);
	return (NULL);
}

static int	get_len_variables(char *str, t_minishell *minishell)
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
			var_value = get_env_value(var_name, minishell);
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

static int	substitute_variable(char *result, int *j, char *str,
				t_minishell *minishell)
{
	char	*var_name;
	char	*var_value;
	int		used;
	int		need_free_value;

	var_name = get_var_name(str);
	var_value = get_env_value(var_name, minishell);
	need_free_value = 0;
	if (var_name && var_name[0] == '$' && (var_name[1] == '?'
			|| var_name[1] == '$'))
		need_free_value = 1;
	if (var_value)
	{
		ft_strlcpy(&result[*j], var_value, ft_strlen(var_value) + 1);
		*j += ft_strlen(var_value);
		if (need_free_value)
			free(var_value);
	}
	used = ft_strlen(var_name);
	free(var_name);
	return (used);
}

char	*expand_variables(char *str, t_minishell *minishell)
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
	result = malloc(get_len_variables(str, minishell));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && in_quotes == 0)
			in_dquotes = !in_dquotes;
		else if (str[i] == '\'' && in_dquotes == 0)
			in_quotes = !in_quotes;
		if (str[i] == '$' && in_quotes != 1)
			i += substitute_variable(result, &j, &str[i], minishell);
		else
			result[j++] = str[i++];
	}
	return (result[j] = '\0', result);
}
