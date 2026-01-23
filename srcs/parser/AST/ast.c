#include "minishell.h"

t_list	*lst_go_to(t_list *lst, int position)
{
	int	i;

	i = 0;
	while (i < position)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

int	switch_p(int type, int p)
{
	if (type == OPEN_BRACKET)
		p++;
	if (type == CLOSE_BRACKET)
		p--;
	return (p);
}

void	remove_parenthesis(t_ast *node, int p)
{
	int		i;
	t_list	*lst_token;
	t_token	*token;

	lst_token = node->lst_token;
	token = lst_token->content;
	i = 0;
	while (i++ < node ->lst_len - 1)
	{
		p = switch_p(token->type, p);
		if (p == 0)
			return ;
		lst_token = lst_token->next;
		token = lst_token->content;
	}
	if (token->type != CLOSE_BRACKET)
		return ;
	node->is_subshell = true;
	lst_token = node->lst_token;
	lst_token = lst_token->next;
	node->lst_token = lst_token;
	node->lst_len -= 2;
	remove_parenthesis(node, 0);
}

int	is_op(t_token_type t)
{
	if (t == AND || t == OR)
		return (1);
	return (0);
}

int	is_pipe(t_token_type t)
{
	if (t == PIPE)
		return (1);
	return (0);
}

void	new_node(t_ast *node, t_list *lst_token, int i, enum e_token_type token_type)
{
	t_ast	*node_left;
	t_ast	*node_right;

	node_left = ft_astnew(node->lst_token, i);
	node_left->lst_len = i;
	node_right = ft_astnew(lst_token->next, node->lst_len - i - 1);
	node_right->lst_len = node->lst_len - i - 1;
	node->lst_token = lst_token;
	node->exec_token = ft_calloc(sizeof(char *), 1);
	node->exec_lst = NULL;
	node->redirs = NULL;
	node->lst_len = 1;
	node->node_type = token_type;
	node->next_left = node_left;
	node->next_right = node_right;
	create_ast(node_left);
	create_ast(node_right);
}

void	create_ast(t_ast *node)
{
	int		i;
	t_list	*lst_token;
	t_token	*token;
	int		p;

	remove_parenthesis(node, 0);
	p = 0;
	i = node->lst_len - 1;
	while (i > 0)
	{
		lst_token = lst_go_to(node->lst_token, i);
		token = lst_token->content;
		if (is_op(token->type) && p == 0)
		{
			new_node(node, lst_token, i, token->type);
			return ;
		}
		if (token->type == OPEN_BRACKET)
			p++;
		if (token->type == CLOSE_BRACKET)
			p--;
		i--;
	}
	p = 0;
	i = i = node->lst_len - 1;
	while (i > 0)
	{
		lst_token = lst_go_to(node->lst_token, i);
		token = lst_token->content;
		if (is_pipe(token->type) && p == 0)
		{
			new_node(node, lst_token, i, token->type);
			return ;
		}
		if (token->type == OPEN_BRACKET)
			p++;
		if (token->type == CLOSE_BRACKET)
			p--;
		i--;
	}
}
