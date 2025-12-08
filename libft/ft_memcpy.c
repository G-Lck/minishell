/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:26:37 by marvin            #+#    #+#             */
/*   Updated: 2025/07/30 23:26:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t	index;

	index = 0;
	if (!destination && !source)
		return (NULL);
	while (index < size)
	{
		((unsigned char *)destination)[index]
			= ((unsigned char *)source)[index];
		index ++;
	}
	return (destination);
}
