/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:36:17 by marvin            #+#    #+#             */
/*   Updated: 2025/07/31 22:36:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t lenght)
{
	size_t	index;

	index = 0;
	if (lenght == 0)
		return (0);
	while (first[index] && index < lenght - 1)
	{
		if (first[index] != second[index])
			break ;
		index ++;
	}
	return ((unsigned char)first[index] - (unsigned char)second[index]);
}
