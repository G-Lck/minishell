/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#              */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_node(t_ast *node, t_list *l_token, int i, enum e_token_type typ)
{
	t_ast	*node_left;
	t_ast	*node_right;

	node_left = ft_astnew(node->lst_token, i);
	node_left->lst_len = i;
	node_right = ft_astnew(l_token->next, node->lst_len - i - 1);
	node_right->lst_len = node->lst_len - i - 1;
	node->lst_token = l_token;
	node->exec_token = NULL;
	node->exec_lst = NULL;
	node->redirs = NULL;
	node->skip = false;
	node->lst_len = 1;
	node->node_type = typ;
	node->next_left = node_left;
	node->next_right = node_right;
	create_ast(node_left);
	create_ast(node_right);
}

static int	find_operator(t_ast *node, int (*check)(t_token_type))
{
	int		i;
	int		p;
	t_list	*lst_token;
	t_token	*token;

	p = 0;
	i = node->lst_len - 1;
	while (i > 0)
	{
		lst_token = lst_go_to(node->lst_token, i);
		token = lst_token->content;
		if (check(token->type) && p == 0)
			return (i);
		p = switch_p(token->type, p);
		i--;
	}
	return (-1);
}

void	create_ast(t_ast *node)
{
	int		i;
	t_list	*lst_token;
	t_token	*token;

	remove_parenthesis(node, 0);
	i = find_operator(node, is_op);
	if (i == -1)
		i = find_operator(node, is_pipe);
	if (i == -1)
		return ;
	lst_token = lst_go_to(node->lst_token, i);
	token = lst_token->content;
	new_node(node, lst_token, i, token->type);
}
