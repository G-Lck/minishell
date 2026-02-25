/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c           .                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:36:17 by marvin            #+#    #+#             */
/*   Updated: 2025/07/31 22:36:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *first, const char *second)
{
	size_t	index;

	index = 0;
	while (first[index] && second[index])
	{
		if (first[index] != second[index])
			break ;
		index ++;
	}
	return ((unsigned char)first[index] - (unsigned char)second[index]);
}
