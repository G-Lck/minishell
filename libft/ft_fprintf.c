/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:18:32 by theo              #+#    #+#             */
/*   Updated: 2025/10/13 17:36:34 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_formats_fd(int fd, va_list *args, char format)
{
	size_t	readed_char;

	readed_char = 0;
	if (format == 'c')
		readed_char += ft_printf_char_fd(fd, va_arg(*args, int));
	else if (format == 's')
		readed_char += ft_printf_putstr_fd(fd, va_arg(*args, char *));
	else if (format == '%')
		readed_char += ft_printf_char_fd(fd, '%');
	else if (format == 'p')
		readed_char += ft_print_ptr_fd(fd, va_arg(*args, uintptr_t));
	else if (format == 'd' || format == 'i')
		readed_char += ft_print_numberfd(fd, va_arg(*args, int));
	else if (format == 'x')
		readed_char += ft_print_hexadecimal_fd(fd, va_arg(*args, unsigned int), 0);
	else if (format == 'X')
		readed_char += ft_print_hexadecimal_fd(fd, va_arg(*args, unsigned int), 1);
	else if (format == 'u')
		readed_char += ft_print_number_fd(fd, va_arg(*args, unsigned int));
	return (readed_char);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	int		index;
	size_t	total;
	va_list	args;

	index = 0;
	total = 0;
	va_start(args, str);
	while (str[index])
	{
		if (str[index] != '%')
			total += write (fd, str + index, 1);
		else
			total += ft_formats_fd(fd, &args, str[++index]);
		index ++;
	}
	va_end(args);
	return (total);
}
