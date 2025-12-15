#include "ast.h"

t_ast	*ft_astnew(t_list *lst_token, int len)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->lst_token = lst_token;
	node->lst_len = len;
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
