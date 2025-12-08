/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:30:40 by marvin            #+#    #+#             */
/*   Updated: 2025/07/31 22:30:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchChar)
{
	int	index;

	index = ft_strlen(string);
	while (index >= 0)
	{
		if (string[index] == (unsigned char)searchChar)
			return ((char *)string + index);
		index --;
	}
	return (NULL);
}
