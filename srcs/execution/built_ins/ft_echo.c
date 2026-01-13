/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_option_n(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, t_env *env)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_option_n(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", expand_variables(args[i], env));
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
