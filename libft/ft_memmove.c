/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 12:32:41 by theo              #+#    #+#             */
/*   Updated: 2025/08/03 12:33:39 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*source;
	char		*destination;

	i = 0;
	source = (char *)src;
	destination = (char *)dst;
	if (dst != NULL || src != NULL)
	{
		if (destination > source)
		{
			while (len-- > 0)
				destination[len] = source[len];
		}
		else
		{
			while (i < len)
			{
				destination[i] = source[i];
				i++;
			}
		}
		return (dst);
	}
	return (NULL);
}
