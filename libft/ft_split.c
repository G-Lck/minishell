/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:24:16 by theo              #+#    #+#             */
/*   Updated: 2025/08/03 11:30:12 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_size(char const *str, char separator)
{
	int	index;
	int	size;

	index = 0;
	size = 0;
	while (str[index])
	{
		if (str[index] != separator)
		{
			size ++;
			while (str[index + 1] && str[index + 1] != separator)
				index ++;
		}
		index ++;
	}
	return (size);
}

void	allocation(char const *str, char separator, char **ptr)
{
	int	index;
	int	ptr_index;
	int	size;

	index = 0;
	ptr_index = 0;
	while (str[index])
	{
		if (str[index] != separator)
		{
			size = 0;
			while (str[index + 1] && str[index + 1] != separator)
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

void	fill_tab(char const *str, char separator, char **ptr)
{
	int	index;
	int	ptr_i;
	int	ptr_j;

	index = 0;
	ptr_i = 0;
	while (str[index])
	{
		if (str[index] != separator)
		{
			ptr_j = 0;
			while (str[index + 1] && str[index + 1] != separator)
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

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	ptr = ft_calloc(sizeof(char *), (get_size(s, c) + 1));
	if (!ptr)
		return (NULL);
	allocation(s, c, ptr);
	fill_tab(s, c, ptr);
	return (ptr);
}
