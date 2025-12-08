/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:26:22 by marvin            #+#    #+#             */
/*   Updated: 2025/07/31 13:26:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchChar)
{
	size_t	index;

	index = 0;
	while (string[index] != (unsigned char)searchChar)
	{
		if (string[index] == '\0')
			return (NULL);
		index ++;
	}
	return ((char *)string + index);
}
