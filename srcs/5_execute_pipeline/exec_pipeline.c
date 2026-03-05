/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_ast *node, t_minishell *minishell,
	t_pipeline *pipeline, int cmd_index)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	command_preparation(node, minishell);
	setup_pipe_redirections(pipeline->pipes_tab, cmd_index,
		pipeline->total_cmds, node);
	close_all_pipes(pipeline->pipes_tab, pipeline->total_pipe);
	node->exec_token = tokens_to_args(node->exec_lst);
	exec_node(node, minishell);
	exit(minishell->status);
}

static void	parent_close_used(t_pipeline *pipeline, int cmd_index)
{
	if (cmd_index > 0 && pipeline->pipes_tab[cmd_index - 1][0] != -1)
	{
		close(pipeline->pipes_tab[cmd_index - 1][0]);
		pipeline->pipes_tab[cmd_index - 1][0] = -1;
	}
	if (cmd_index < pipeline->total_cmds - 1
		&& pipeline->pipes_tab[cmd_index][1] != -1)
	{
		close(pipeline->pipes_tab[cmd_index][1]);
		pipeline->pipes_tab[cmd_index][1] = -1;
	}
}

static void	exec_recursive(t_ast *node, t_minishell *minishell,
	t_pipeline *pipeline, int *cmd_index)
{
	pid_t	pid;

	if (!node)
		return ;
	if (node->node_type == CMD)
	{
		signal(SIGINT, sigint_exec);
		signal(SIGQUIT, sigquit_exec);
		pid = fork();
		if (pid == -1)
			return (perror("Fork failed"));
		if (pid == 0)
			child_process(node, minishell, pipeline, *cmd_index);
		pipeline->pids[*cmd_index] = pid;
		parent_close_used(pipeline, *cmd_index);
		(*cmd_index)++;
		return ;
	}
	if (node->node_type == PIPE_OP)
	{
		exec_recursive(node->next_left, minishell, pipeline, cmd_index);
		exec_recursive(node->next_right, minishell, pipeline, cmd_index);
	}
}

void	exec_pipeline(t_ast *node, t_minishell *minishell)
{
	t_pipeline	*pipeline;
	int			cmd_index;

	pipeline = init_pipeline(node);
	if (!pipeline)
		return ;
	cmd_index = 0;
	exec_recursive(node, minishell, pipeline, &cmd_index);
	wait_pipeline(pipeline, minishell);
	cleanup_pipeline(pipeline);
}
