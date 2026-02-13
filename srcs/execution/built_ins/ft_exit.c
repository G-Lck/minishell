/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	cleanup_minishell(t_minishell *minishell)
{
	if (minishell->tokens_list)
	{
		free_token_list(&minishell->tokens_list);
		minishell->tokens_list = NULL;
	}
	if (minishell->ast)
	{
		free_ast(minishell->ast);
		minishell->ast = NULL;
	}
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	if (minishell->env)
	{
		free_env(&minishell->env);
		minishell->env = NULL;
	}
	if (minishell->current_dir)
	{
		free(minishell->current_dir);
		minishell->current_dir = NULL;
	}
}

int	ft_exit(char **args, t_minishell *minishell)
{
	if (!args[1])
	{
		minishell->exit_code = minishell->last_status;
	}
	else if (!ft_isnumber(args[1]))
	{
		ft_fprintf(2, "exit: numeric argument required\n");
		minishell->exit_code = 255;
	}
	else if (args[2])
	{
		ft_fprintf(2, "exit: too many arguments\n");
		return (1);
	}
	else
		minishell->exit_code = ft_atoi(args[1]) % 256;
	cleanup_minishell(minishell);
	exit(minishell->exit_code);
	return (EXIT_SHELL);
}
