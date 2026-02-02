/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:24:16 by theo              #+#    #+#             */
/*   Updated: 2026/01/26 12:27:21 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char *set, char c)
{
	int	index;

	index = 0;
	while (set[index])
	{
		if (set[index] == c)
			return (1);
		index ++;
	}
	return (0);
}

int	get_size(char const *str, char *set)
{
	int	index;
	int	size;

	index = 0;
	size = 0;
	while (str[index])
	{
		if (!is_sep(set, str[index]))
		{
			size ++;
			while (str[index + 1] && !is_sep(set, str[index + 1]))
				index ++;
		}
		index ++;
	}
	return (size);
}

void	allocation(char const *str, char *set, char **ptr)
{
	int	index;
	int	ptr_index;
	int	size;

	index = 0;
	ptr_index = 0;
	while (str[index])
	{
		if (!is_sep(set, str[index]))
		{
			size = 0;
			while (str[index + 1] && !is_sep(set, str[index + 1]))
			{
				size ++;
				index ++;
			}
			ptr[ptr_index] = ft_calloc(sizeof(char), size + 2);
			if (!ptr)
				return ;
			ptr_index ++;
		}
		index ++;
	}
}

void	fill_tab(char const *str, char *set, char **ptr)
{
	int	index;
	int	ptr_i;
	int	ptr_j;

	index = 0;
	ptr_i = 0;
	while (str[index])
	{
		if (!is_sep(set, str[index]))
		{
			ptr_j = 0;
			while (str[index + 1] && !is_sep(set, str[index + 1]))
			{
				ptr[ptr_i][ptr_j] = str[index];
				ptr_j ++;
				index ++;
			}
			ptr[ptr_i][ptr_j] = str[index];
			ptr_i ++;
		}
		index ++;
	}
}

char	**ft_split(char const *s, char *set)
{
	char	**ptr;

	ptr = ft_calloc(sizeof(char *), (get_size(s, set) + 1));
	if (!ptr)
		return (NULL);
	allocation(s, set, ptr);
	fill_tab(s, set, ptr);
	return (ptr);
}
