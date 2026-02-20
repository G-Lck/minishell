/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void exec_node(t_ast *node, t_minishell *minishell)
{
	char	**args;
	int		builtin_status;

	args = node->exec_token;
	if (!node || !node->exec_token)
		exit(EXIT_FAILURE);
	if (!args)
		exit(EXIT_FAILURE);
	builtin_status = is_builtin_and_execute(args, minishell);
	if (builtin_status != -1)
	{
		//free_args(args);
		minishell->last_status = builtin_status;
		exit(builtin_status);
	}
	exec_in_pipeline(node, minishell);
	return ;
}

void exec_node_no_pipeline(t_ast *node, t_minishell *minishell)
{
	char	**args;
	int		builtin_status;
	int		saved_stdin;
	int		saved_stdout;

	args = node->exec_token;
	if (!node || !node->exec_token)
		exit(EXIT_FAILURE);
	if (!args)
		exit(EXIT_FAILURE);
	builtin_status = is_builtin(args);
	if (builtin_status == 1)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (apply_redirections_safe(node) == -1)
		{
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			free_args(args);
			minishell->last_status = 1;
			return ;
		}
		builtin_status = is_builtin_and_execute(args, minishell);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		//free_args(args);
		minishell->last_status = builtin_status;
		return ;
	}
	exec_no_pipeline(node, minishell);
	return ;
}
