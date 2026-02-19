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

#include "minishell.h"

char	*get_env_value(char *key, t_minishell *minishell)
{
	t_env	*var;

	if (!key)
		return (NULL);
	if (key[0] == '\0')
		return (ft_strdup("$"));

	// Variables spéciales qui commencent par $
	if (key[0] == '$')
	{
		if (key[1] == '?' && key[2] == '\0')
			return (ft_itoa(minishell->previous_last_status));
		if (key[1] == '$')
			return (ft_itoa(getpid()));
		// Pour $0, $1, $2, etc. - pas implémenté pour l'instant
		if (ft_isdigit(key[1]))
			return (ft_strdup(""));

		// Variable normale - enlever le $ et chercher dans l'environnement
		var = find_env_var(minishell->env, &key[1]);
		if (var)
			return (var->value);
		return (NULL);
	}

	// Si pas de $, chercher directement (ne devrait pas arriver normalement)
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

static int	substitute_variable(char *result, int *j, char *str, t_minishell *minishell)
{
	char	*var_name;
	char	*var_value;
	int		used;
	int		need_free_value;

	var_name = get_var_name(str);
	var_value = get_env_value(var_name, minishell);

	// Déterminer si var_value doit être libérée (variables spéciales comme $?, $$)
	need_free_value = 0;
	if (var_name && var_name[0] == '$' && (var_name[1] == '?' || var_name[1] == '$'))
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
	result[j] = '\0';
	return (result);
}
