/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:20:07 by marvin            #+#    #+#             */
/*   Updated: 2025/08/02 11:20:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	int		index;
	char	*ptr;

	index = 0;
	if (!source)
		return (NULL);
	ptr = ft_calloc(ft_strlen(source) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (source[index])
	{
		ptr[index] = source[index];
		index ++;
	}
	return (ptr);
}
