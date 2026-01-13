/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_variable(char *arg, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (1);
	}
	set_env_var(env, key, value);
	free(key);
	free(value);
	return (0);
}

static void	print_sorted_env(t_env *env)
{
	char	**sorted;
	int		count;

	count = count_env_vars(env);
	sorted = create_sorted_array(env, count);
	if (!sorted)
		return ;
	bubble_sort_array(sorted, count);
	print_and_free_array(sorted);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	ret;

	ret = 0;
	if (!args || !args[0])
	{
		print_sorted_env(*env);
		return (0);
	}
	i = 0;
	while (args[i])
	{
		if (export_variable(args[i], env) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
