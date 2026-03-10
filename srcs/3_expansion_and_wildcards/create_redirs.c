/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:00:00 by glucken           #+#    #+#             */
/*   Updated: 2026/03/10 23:00:00 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_expand_var(char *f, t_ast *n, t_list **node, t_minishell *m)
{
	char	*expvar;

	if (ft_strlen(f) == 1)
	{
		*node = new_redir_node("$", 0);
		return (ft_lstadd_back(&n->redirs, *node), 1);
	}
	expvar = expand_variables(f, m);
	if (ft_strlen(expvar) == 0 || (expvar != NULL && check_wspaces(expvar)))
		n->skip = true;
	*node = new_redir_node(expvar, 0);
	free(expvar);
	return (2);
}

static int	redir_no_dollar(char *f, t_token_type t, t_list **node,
	t_minishell *m)
{
	char	*expvar;

	expvar = expand_variables(f, m);
	*node = new_redir_node(expvar, t);
	free(expvar);
	if (!*node)
		return (0);
	return (1);
}

static int	redir_heredoc(char *f, t_ast *n)
{
	t_list	*new_node;

	new_node = new_redir_node(f, HERE_DOC);
	if (!new_node)
		return (0);
	ft_lstadd_back(&n->redirs, new_node);
	return (1);
}

int	create_redirs(char *f, t_token_type type, t_ast *n, t_minishell *m)
{
	t_list	*new_node;

	if (type == HERE_DOC)
		return (redir_heredoc(f, n));
	if (f[0] != '$')
	{
		if (!redir_no_dollar(f, type, &new_node, m))
			return (0);
	}
	else
	{
		if (redir_expand_var(f, n, &new_node, m) == 1)
			return (1);
	}
	if (n->skip == true)
		ft_printf("ambiguous redirection\n");
	return (ft_lstadd_back(&n->redirs, new_node), 1);
}
