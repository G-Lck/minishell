/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:40 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/17 17:17:46 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	char_isfind(char *str, char c)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		if (str[index] == c)
			return (1);
		index ++;
	}
	return (0);
}

char	*ft_realloc(char *dest, char *src)
{
	char	*tmp;
	int		index;
	int		index_2;

	index = 0;
	index_2 = 0;
	tmp = ft_strdup(dest);
	free (dest);
	dest = ft_calloc(ft_strlen(tmp) + ft_strlen(src) + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (tmp[index_2])
		dest[index ++] = tmp[index_2 ++];
	index_2 = 0;
	while (src[index_2])
		dest[index ++] = src[index_2 ++];
	free (tmp);
	return (dest);
}
