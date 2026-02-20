/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_pipe_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_pipe_input(int **pipes, int idx, t_ast *node)
{
	int	fd;

	fd = open_redir_fd(node, REDIR_IN);
	if (fd == -2)
		exit(EXIT_FAILURE);
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (idx > 0)
	{
		dup2(pipes[idx - 1][0], STDIN_FILENO);
		close(pipes[idx - 1][0]);
		pipes[idx - 1][0] = -1;
	}
}

static void	setup_pipe_output(int **pipes, int idx, int total, t_ast *node)
{
	int	fd;

	fd = open_redir_fd(node, REDIR_OUT);
	if (fd == -1)
		fd = open_redir_fd(node, APPEND);
	if (fd == -2)
		exit(EXIT_FAILURE);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (idx < total - 1)
	{
		dup2(pipes[idx][1], STDOUT_FILENO);
		close(pipes[idx][1]);
		pipes[idx][1] = -1;
	}
}

void	setup_pipe_redirections(int **pipes, int idx,
	int total, t_ast *node)
{
	setup_pipe_input(pipes, idx, node);
	setup_pipe_output(pipes, idx, total, node);
}
