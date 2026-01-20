/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance           #+#    #+#             */
/*   Updated: 2026/01/16 16:22:37 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_var(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	add_env_var(t_env **head, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = create_env_var(key, value);
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*find_env_var(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env_var(t_env **env, char *key, char *value)
{
	t_env	*var;

	var = find_env_var(*env, key);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
		return ;
	}
	add_env_var(env, key, value);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	feel_env(t_env **env, char *envp[])
{
	char	**splited_env_var;
	int		index;

	index = 0;
	while (envp[index])
	{
		splited_env_var = ft_split(envp[index], '=');
		if (!splited_env_var)
			return (0);
		add_env_var(env, splited_env_var[0], splited_env_var[1]);
		free(splited_env_var[0]);
		free(splited_env_var[1]);
		free(splited_env_var);
		index ++;
	}
	return (1);
}