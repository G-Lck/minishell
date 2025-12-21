/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:55:30 by theo              #+#    #+#             */
/*   Updated: 2025/10/13 17:36:31 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_hex_fd(int fd, unsigned long number, size_t *readed_char, char *base)
{
	if (number >= 16)
	{
		ft_print_hex_fd(fd, number / 16, readed_char, base);
		ft_print_hex_fd(fd, number % 16, readed_char, base);
	}
	if (number < 16)
	{
		ft_putchar_fd(fd, base[number]);
		(*readed_char)++;
	}
}

void	ft_put_number_fd(int fd, long long number, size_t *readed_char)
{
	if (number < 0)
	{
		(*readed_char) += write (1, "-", 1);
		number *= -1;
	}
	if (number >= 10)
	{
		ft_put_number_fd(fd, number / 10, readed_char);
		ft_put_number_fd(fd, number % 10, readed_char);
	}
	if (number < 10)
	{
		ft_putchar_fd(fd, number + 48);
		(*readed_char)++;
	}
}

size_t	ft_print_number_fd(int fd, long long number)
{
	size_t	readed_char;

	readed_char = 0;
	if (number == -2147483648)
		readed_char = write (fd, "-2147483648", 11);
	else
		ft_put_number_fd(fd, number, &readed_char);
	return (readed_char);
}

size_t	ft_print_ptr_fd(int fd, uintptr_t ptr)
{
	size_t	readed_char;

	readed_char = 0;
	if (!ptr)
	{
		write (fd, "(nil)", 5);
		return (5);
	}
	write (fd, "0x", 2);
	ft_print_hex_fd(fd, ptr, &readed_char, "0123456789abcdef");
	return (readed_char + 2);
}

size_t	ft_print_hexadecimal_fd(int fd, unsigned long number, int upper)
{
	size_t	readed_char;

	readed_char = 0;
	if (upper == 0)
		ft_print_hex_fd(fd, number, &readed_char, "0123456789abcdef");
	else
		ft_print_hex_fd(fd, number, &readed_char, "0123456789ABCDEF");
	return (readed_char);
}
