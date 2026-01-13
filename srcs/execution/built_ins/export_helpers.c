/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_vars(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**create_sorted_array(t_env *env, int count)
{
	t_env	*tmp;
	char	**sorted;
	int		i;

	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		sorted[i] = ft_strjoin(tmp->key, "=");
		if (sorted[i])
			sorted[i] = ft_strjoin(sorted[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	sorted[count] = NULL;
	return (sorted);
}

void	bubble_sort_array(char **sorted, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(sorted[j], sorted[j + 1], ft_strlen(sorted[j])) > 0)
			{
				temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_and_free_array(char **sorted)
{
	int	i;

	i = 0;
	while (sorted[i])
	{
		ft_printf("declare -x %s\n", sorted[i]);
		free(sorted[i]);
		i++;
	}
	free(sorted);
}
