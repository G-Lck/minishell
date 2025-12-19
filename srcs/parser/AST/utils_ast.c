#include "ast.h"

t_ast	*ft_astnew(t_list *lst_token, int len)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->lst_token = lst_token;
	node->lst_len = len;
	node->is_subshell = false;
	node->node_type = 3;
	node->next_left = NULL;
	node->next_right = NULL;
	return (node);
}

void	print_ast(t_ast *node)
{
	t_list	*lst_token;
	t_token	*token;

	lst_token = node->lst_token;
	token = lst_token->content;
	ft_printf(" %s\n", token->literal);
	if (node->next_left != NULL && node->next_right != NULL)
	{
		ft_printf("left");
		print_ast(node->next_left);
		ft_printf("right");
		print_ast(node->next_right);
	}
	return ;
}

static void	print_node_label(t_ast *node)
{
	t_list	*lst;
	t_token	*tok;
	int		i;

	if (!node || !node->lst_token)
		return ;
	lst = node->lst_token;
	tok = lst->content;
	if (node->lst_len == 1 && (tok->type == AND || tok->type == OR || tok->type == PIPE))
		ft_printf("\"%s\"", tok->literal);
	else
	{
		i = 0;
		while (i < node->lst_len && lst)
		{
			tok = lst->content;
			ft_printf("\"%s\"", tok->literal);
			if (i < node->lst_len - 1)
				ft_printf(" ");
			lst = lst->next;
			i++;
		}
	}
	if (node->is_subshell)
		ft_printf(" (subshell)");
}

static void	print_subtree(t_ast *node, char *prefix, int is_last)
{
	char	*branch;
	char	*next_prefix;

	if (!node)
		return ;
	branch = "  |-- ";
	ft_printf("%s%s", prefix, branch);
	print_node_label(node);
	ft_printf("\n");
	/* build next prefix */
	if (is_last)
		next_prefix = ft_strjoin(prefix, "      ");
	else
		next_prefix = ft_strjoin(prefix, "  |   ");
	if (node->next_left && node->next_right)
	{
		print_subtree(node->next_left, next_prefix, 0);
		print_subtree(node->next_right, next_prefix, 1);
	}
	else if (node->next_left)
		print_subtree(node->next_left, next_prefix, 1);
	else if (node->next_right)
		print_subtree(node->next_right, next_prefix, 1);
	free(next_prefix);
}

void	print_ast_pretty(t_ast *node)
{
	if (!node)
		return ;
	/* root label */
	print_node_label(node);
	ft_printf("\n");
	if (node->next_left && node->next_right)
	{
		print_subtree(node->next_left, "", 0);
		print_subtree(node->next_right, "", 1);
	}
	else if (node->next_left)
		print_subtree(node->next_left, "", 1);
	else if (node->next_right)
		print_subtree(node->next_right, "", 1);
}
