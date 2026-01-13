/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* grosse discussion ici, dans mon bash je nai jamais derreur mais
j ai lu que je devrais en avoir et retourner parfois 1 a discuter*/
static int	is_valid_unset_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_first_env_var(t_env **env)
{
	t_env	*to_remove;

	to_remove = *env;
	*env = (*env)->next;
	free(to_remove->key);
	free(to_remove->value);
	free(to_remove);
}

static int	remove_from_middle(t_env *env, char *key)
{
	t_env	*prev;
	t_env	*current;

	prev = env;
	current = env->next;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

static int	remove_env_var(t_env **env, char *key)
{
	if (!env || !*env || !key)
		return (0);
	if (ft_strncmp((*env)->key, key, ft_strlen(key) + 1) == 0)
	{
		remove_first_env_var(env);
		return (1);
	}
	return (remove_from_middle(*env, key));
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	ret;

	ret = 0;
	if (!args || !args[0])
		return (0);
	i = 0;
	while (args[i])
	{
		if (!is_valid_unset_identifier(args[i]))
		{
			ft_fprintf(2, "minishell: unset: `%s': not a valid identifier\n",
				args[i]);
			ret = 1;
		}
		else
		{
			remove_env_var(env, args[i]);
		}
		i++;
	}
	return (ret);
}
