/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:43:24 by marvin            #+#    #+#             */
/*   Updated: 2025/08/02 19:43:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_character(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		index;
	int		start;
	int		end;

	start = 0;
	index = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && check_character(s1[start], set))
		start ++;
	while (end != 0 && check_character(s1[end], set))
		end --;
	if ((end - start < 0))
	{
		ptr = ft_calloc(1, sizeof(char));
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	ptr = ft_calloc((end - start) + 2, sizeof(char));
	if (!ptr)
		return (NULL);
	while (start <= end)
		ptr[index ++] = s1[start ++];
	return (ptr);
}
