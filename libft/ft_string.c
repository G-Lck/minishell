/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:13:10 by theo              #+#    #+#             */
/*   Updated: 2025/10/13 17:37:09 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

size_t	ft_printf_putstr(char *str)
{
	size_t	readed_char;

	readed_char = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[readed_char])
	{
		write (1, str + readed_char, 1);
		readed_char ++;
	}
	return (readed_char);
}

size_t	ft_printf_char(int character)
{
	size_t	total;
	char	casted_char;

	casted_char = (char) character;
	total = write (1, &casted_char, 1);
	return (total);
}
