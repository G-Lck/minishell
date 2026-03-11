/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:08:35 by theo              #+#    #+#             */
/*   Updated: 2026/01/29 18:14:48 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_minishell *minishell, int exit_code)
{
	cleanup_minishell(minishell);
	return (exit(exit_code));
}

void	clean_exit_pipeline(t_minishell *minishell, t_pipeline *p, int code)
{
	cleanup_minishell(minishell);
	cleanup_pipeline(p);
	return (exit(code));
}

void	free_minishell(t_minishell *minishell)
{
	free(minishell->current_dir);
	free_env(&minishell->env);
}

void	free_tab(char **tab)
{
	int	index;

	index = 0;
	while (tab[index])
	{
		free (tab[index]);
		index ++;
	}
	free(tab);
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
