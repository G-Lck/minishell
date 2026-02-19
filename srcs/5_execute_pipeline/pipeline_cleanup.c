/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_pipes_tab(int **pipes_tab, int pipe_count)
{
	int	i;

	if (!pipes_tab)
		return ;
	i = -1;
	while (++i < pipe_count)
	{
		if (pipes_tab[i])
			free(pipes_tab[i]);
	}
	free(pipes_tab);
}

void	close_all_pipes(int **pipes_tab, int pipe_count)
{
	int	i;

	if (!pipes_tab)
		return ;
	i = -1;
	while (++i < pipe_count)
	{
		if (pipes_tab[i])
		{
			if (pipes_tab[i][0] != -1)
				close(pipes_tab[i][0]);
			if (pipes_tab[i][1] != -1)
				close(pipes_tab[i][1]);
		}
	}
}

void	cleanup_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	if (pipeline->pipes_tab)
		cleanup_pipes_tab(pipeline->pipes_tab, pipeline->total_pipe);
	if (pipeline->pids)
		free(pipeline->pids);
	free(pipeline);
}

void	wait_pipeline(t_pipeline *pipeline, t_minishell *minishell)
{
	int		status;
	int		i;

	i = -1;
	while (++i < pipeline->total_cmds)
	{
		while (waitpid(pipeline->pids[i], &status, 0) == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("waitpid failed");
			minishell->last_status = 1;
			return ;
		}
		if (i == pipeline->total_cmds - 1)
		{
			if (WIFEXITED(status))
				minishell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				minishell->last_status = 128 + WTERMSIG(status);
		}
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
