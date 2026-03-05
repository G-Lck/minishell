/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance           #+#    #+#             */
/*   Updated: 2026/03/05 23:06:57 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	(void)argv;
	if (argc > 1)
		return (ft_fprintf(2, "minishell: no arguments expected\n"), 1);
	init_minishell(&minishell, envp);
	if (!fill_env(&minishell.env, envp))
		return (1);
	g_sig = 0;
	init_signals();
	while (1)
	{
		safe_readline(&minishell.input);
		if (!process_input(&minishell))
			break ;
	}
	rl_clear_history();
	free_minishell(&minishell);
	return (0);
}
