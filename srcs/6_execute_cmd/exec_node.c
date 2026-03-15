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

void	exec_node(t_ast *node, t_minishell *mini, t_pipeline *pipeline)
{
	char	**args;
	int		builtin_status;

	args = node->exec_token;
	if (node->skip == true)
	{
		mini->status = 1;
		return ;
	}
	if (!node || !node->exec_token)
		return ;
	if (!args)
		return ;
	builtin_status = is_builtin_and_execute(args, mini);
	if (builtin_status != -1)
	{
		mini->status = builtin_status;
		clean_exit_pipeline(mini, pipeline, builtin_status);
	}
	try_execve_pipeline(node, mini, pipeline);
	return ;
}

static void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static void	exec_builtin_redir(t_ast *node, t_minishell *minishell)
{
	int		saved_stdin;
	int		saved_stdout;
	int		builtin_status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections_safe(node) == -1)
	{
		restore_fds(saved_stdin, saved_stdout);
		minishell->status = 1;
		return ;
	}
	builtin_status = is_builtin_and_execute(node->exec_token, minishell);
	restore_fds(saved_stdin, saved_stdout);
	minishell->status = builtin_status;
}

void	exec_node_no_pipeline(t_ast *node, t_minishell *minishell)
{
	char	**args;

	args = node->exec_token;
	if (node->skip == true)
	{
		minishell->status = 1;
		return ;
	}
	if (!node || !node->exec_token)
		return ;
	if (!args)
		return ;
	if (is_builtin(args) == 1)
	{
		exec_builtin_redir(node, minishell);
		return ;
	}
	exec_no_pipeline(node, minishell);
}
