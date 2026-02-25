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

static t_redir	*find_heredoc(t_ast *node)
{
	t_list	*cur;
	t_redir	*redir;

	if (!node || !node->redirs)
		return (NULL);
	cur = node->redirs;
	while (cur)
	{
		redir = (t_redir *)cur->content;
		if (redir->redir_type == HERE_DOC)
			return (redir);
		cur = cur->next;
	}
	return (NULL);
}

static int	apply_heredoc_input(t_ast *node)
{
	int		pipefd[2];
	t_redir	*heredoc;

	heredoc = find_heredoc(node);
	if (!heredoc)
		return (0);
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	write(pipefd[1], heredoc->target, ft_strlen(heredoc->target));
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (1);
}

static void	setup_pipe_input(int **pipes, int idx, t_ast *node)
{
	int	fd;

	if (apply_heredoc_input(node))
		return ;
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
