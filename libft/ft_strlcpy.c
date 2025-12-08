/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:10:59 by marvin            #+#    #+#             */
/*   Updated: 2025/07/31 13:10:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (size != 0)
	{
		while (src[index] && index < (size - 1))
		{
			dest[index] = src[index];
			index ++;
		}
		dest[index] = '\0';
	}
	return (ft_strlen(src));
}
