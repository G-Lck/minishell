/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:40:14 by marvin            #+#    #+#             */
/*   Updated: 2025/08/01 17:40:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *string, const char *to_find, size_t len)
{
	size_t	index;
	size_t	check;
	size_t	saved_index;

	index = 0;
	check = 0;
	saved_index = 0;
	if (to_find[0] == '\0')
		return ((char *)string);
	while (string[index])
	{
		saved_index = index;
		while (string[index] && to_find[check]
			&& string[index] == to_find[check] && index < len)
		{
			index ++;
			check ++;
			if (check == ft_strlen(to_find))
				return ((char *)string + saved_index);
		}
		check = 0;
		index = saved_index;
		index ++;
	}
	return (NULL);
}
