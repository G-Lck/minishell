/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 12:01:09 by theo              #+#    #+#             */
/*   Updated: 2025/08/03 12:10:42 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		index;

	ptr = ft_strdup(s);
	if (!ptr)
		return (NULL);
	index = 0;
	while (s[index])
	{
		ptr[index] = (*f)(index, ptr[index]);
		index ++;
	}
	return (ptr);
}
