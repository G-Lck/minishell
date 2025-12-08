/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:47:24 by marvin            #+#    #+#             */
/*   Updated: 2025/07/31 09:47:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *destination, const char *source, size_t size)
{
	size_t	index_a;
	size_t	index_b;
	size_t	return_value;

	index_b = 0;
	index_a = ft_strlen(destination);
	return_value = index_a + ft_strlen(source);
	if (ft_strlen(destination) >= size)
		return (ft_strlen(source) + size);
	while (source[index_b] && index_a < (size - 1))
		destination[index_a++] = source[index_b++];
	destination[index_a] = '\0';
	return (return_value);
}
