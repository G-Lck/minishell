/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipeline_commands(t_ast *node)
{
	if (!node)
		return (0);
	if (node->node_type == CMD)
		return (1);
	if (node->node_type == PIPE_OP)
		return (count_pipeline_commands(node->next_left)
			+ count_pipeline_commands(node->next_right));
	return (0);
}

static int	**create_pipes_tab(int pipe_count)
{
	int	**pipes_tab;
	int	i;

	if (pipe_count <= 0)
		return (NULL);
	pipes_tab = malloc(sizeof(int *) * pipe_count);
	if (!pipes_tab)
		return (NULL);
	i = -1;
	while (++i < pipe_count)
	{
		pipes_tab[i] = malloc(sizeof(int) * 2);
		if (!pipes_tab[i] || pipe(pipes_tab[i]) == -1)
		{
			cleanup_pipes_tab(pipes_tab, i);
			return (NULL);
		}
	}
	return (pipes_tab);
}

t_pipeline	*init_pipeline(t_ast *node)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (perror("Failed to allocate pipeline"), NULL);
	pipeline->total_cmds = count_pipeline_commands(node);
	pipeline->total_pipe = pipeline->total_cmds - 1;
	pipeline->pipes_tab = NULL;
	pipeline->pids = malloc(sizeof(pid_t) * pipeline->total_cmds);
	if (!pipeline->pids)
		return (free(pipeline), perror("Failed to allocate PIDs"), NULL);
	if (pipeline->total_pipe > 0)
	{
		pipeline->pipes_tab = create_pipes_tab(pipeline->total_pipe);
		if (!pipeline->pipes_tab)
		{
			free(pipeline->pids);
			free(pipeline);
			return (NULL);
		}
	}
	return (pipeline);
}
