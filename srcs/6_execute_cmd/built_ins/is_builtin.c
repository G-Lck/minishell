/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4)
		return (1);
	if (ft_strncmp(args[0], "cd", 2) == 0 && ft_strlen(args[0]) == 2)
		return (1);
	if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
		return (1);
	if (ft_strncmp(args[0], "export", 6) == 0 && ft_strlen(args[0]) == 6)
		return (1);
	if (ft_strncmp(args[0], "unset", 5) == 0 && ft_strlen(args[0]) == 5)
		return (1);
	if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
		return (1);
	if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		return (1);
	return (0);
}

int	is_builtin_and_execute(char **args, t_minishell *minishell)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4)
		return (ft_echo(args, minishell->env));
	if (ft_strncmp(args[0], "cd", 2) == 0 && ft_strlen(args[0]) == 2)
		return (ft_cd(args, &minishell->env));
	if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
		return (ft_pwd());
	if (ft_strncmp(args[0], "export", 6) == 0 && ft_strlen(args[0]) == 6)
		return (ft_export(args, &minishell->env));
	if (ft_strncmp(args[0], "unset", 5) == 0 && ft_strlen(args[0]) == 5)
		return (ft_unset(args, &minishell->env));
	if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
		return (ft_env(minishell->env));
	if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		return (ft_exit(args, minishell));
	return (-1);
}
