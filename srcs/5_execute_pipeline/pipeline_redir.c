/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_type(t_token_type type, char *target)
{
	if (type == REDIR_IN)
		return (open(target, O_RDONLY));
	else if (type == REDIR_OUT)
		return (open(target, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (type == APPEND)
		return (open(target, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

int	open_redir_fd(t_ast *node, t_token_type type)
{
	t_list	*cur;
	t_redir	*redir;
	int		fd;

	if (!node || !node->redirs)
		return (-1);
	cur = node->redirs;
	while (cur)
	{
		redir = (t_redir *)cur->content;
		if (redir->redir_type == type)
		{
			fd = open_redir_type(type, redir->target);
			if (fd == -1)
				return (perror(redir->target), -2);
			return (fd);
		}
		cur = cur->next;
	}
	return (-1);
}

static int	apply_one_redir(t_redir *redir)
{
	int	fd;

	fd = open_redir_type(redir->redir_type, redir->target);
	if (fd == -1)
		return (perror(redir->target), -1);
	if (redir->redir_type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections_safe(t_ast *node)
{
	t_list	*cur;

	if (!node || !node->redirs)
		return (0);
	cur = node->redirs;
	while (cur)
	{
		if (apply_one_redir((t_redir *)cur->content) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}

void	apply_redirections(t_ast *node)
{
	int	fd;

	if (!node || !node->redirs)
		return ;
	fd = open_redir_fd(node, REDIR_IN);
	if (fd == -2)
		exit(EXIT_FAILURE);
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
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
}
