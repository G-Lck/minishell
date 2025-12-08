/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:32:19 by marvin            #+#    #+#             */
/*   Updated: 2025/08/02 19:32:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		index;
	int		index_2;
	char	*ptr;

	index = 0;
	index_2 = 0;
	ptr = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[index_2])
		ptr[index ++] = s1[index_2 ++];
	index_2 = 0;
	while (s2[index_2])
		ptr[index ++] = s2[index_2 ++];
	return (ptr);
}
