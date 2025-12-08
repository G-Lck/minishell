/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:19:56 by theo              #+#    #+#             */
/*   Updated: 2025/08/03 11:53:39 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(int nb)
{
	int	total;

	total = 0;
	if (nb < 0)
	{
		nb *= -1;
		total ++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		total ++;
	}
	return (total + 2);
}

void	fill_ptr(int nbr, char *ptr, int index)
{
	if (nbr < 0)
		nbr *= -1;
	if (nbr >= 10)
	{
		fill_ptr(nbr / 10, ptr, index - 1);
		fill_ptr(nbr % 10, ptr, index);
	}
	if (nbr <= 9)
		ptr[index] = nbr + 48;
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		index;

	if (n == -2147483648)
	{
		ptr = ft_strdup("-2147483648");
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	index = get_len(n);
	ptr = ft_calloc(sizeof(char), index);
	if (!ptr)
		return (NULL);
	if (n < 0)
		ptr[0] = '-';
	fill_ptr(n, ptr, index - 2);
	return (ptr);
}
