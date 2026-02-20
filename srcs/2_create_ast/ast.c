#include "minishell.h"

static t_list	*lst_go_to(t_list *lst, int position)
{
	int	i;

	i = 0;
	while (i < position && lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

static int	switch_p(int type, int p)
{
	if (type == OPEN_BRACKET)
		p++;
	if (type == CLOSE_BRACKET)
		p--;
	return (p);
}

static void	remove_parenthesis(t_ast *node, int p)
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

static int	is_op(t_token_type t)
{
	if (t == AND || t == OR)
		return (1);
	return (0);
}

static int	is_pipe(t_token_type t)
{
	if (t == PIPE)
		return (1);
	return (0);
}

static void	new_node(t_ast *node, t_list *lst_token, int i, enum e_token_type token_type)
{
	t_ast	*node_left;
	t_ast	*node_right;

	node_left = ft_astnew(node->lst_token, i);
	node_left->lst_len = i;
	node_right = ft_astnew(lst_token->next, node->lst_len - i - 1);
	node_right->lst_len = node->lst_len - i - 1;
	node->lst_token = lst_token;
	node->exec_token = NULL;
	node->exec_lst = NULL;
	node->redirs = NULL;
	node->lst_len = 1;
	node->node_type = token_type;
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
