/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:23:57 by marvin            #+#    #+#             */
/*   Updated: 2025/08/01 17:23:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	size_t	index;

	index = 0;
	if (size == 0)
		return (0);
	while (index < size - 1)
	{
		if (((unsigned char *)pointer1)[index]
			!= ((unsigned char *)pointer2)[index])
			break ;
		index ++;
	}
	return (((unsigned char *)pointer1)[index] -
		((unsigned char *)pointer2)[index]);
}
