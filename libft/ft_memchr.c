/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:05:29 by marvin            #+#    #+#             */
/*   Updated: 2025/08/01 17:05:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchChar, size_t size)
{
	size_t	index;

	index = 0;
	if (size == 0)
		return (NULL);
	while (((unsigned char *)memoryBlock)[index] != (unsigned char)searchChar)
	{
		if (index == size - 1)
			return (NULL);
		index ++;
	}
	return ((void *)memoryBlock + index);
}
