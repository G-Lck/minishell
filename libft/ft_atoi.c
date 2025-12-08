/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:42:13 by marvin            #+#    #+#             */
/*   Updated: 2025/08/01 18:42:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nbr)
{
	int	index;
	int	result;
	int	negative;

	index = 0;
	result = 0;
	negative = 0;
	while ((nbr[index] >= 9 && nbr[index] <= 13) || nbr[index] == 32)
		index++;
	if (nbr[index] == '-' || nbr[index] == '+')
	{
		if (nbr[index] == '-')
			negative = 1;
		index ++;
	}
	while ((nbr[index] >= '0' && nbr[index] <= '9'))
		result = result * 10 + (nbr[index ++] - 48);
	if (negative)
		result *= -1;
	return (result);
}
