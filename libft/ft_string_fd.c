/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:13:10 by theo              #+#    #+#             */
/*   Updated: 2025/10/13 17:37:09 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_printf_putstr_fd(int fd, char *str)
{
	size_t	readed_char;

	readed_char = 0;
	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (str[readed_char])
	{
		write (fd, str + readed_char, 1);
		readed_char ++;
	}
	return (readed_char);
}

size_t	ft_printf_char_fd(int fd, int character)
{
	size_t	total;
	char	casted_char;

	casted_char = (char) character;
	total = write (fd, &casted_char, 1);
	return (total);
}
