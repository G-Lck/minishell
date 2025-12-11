# include "ast.h"

void	ft_astadd_left(t_ast **ast, t_ast *new)
{
	if (ast == NULL)
		return ;
	if (*ast == NULL)
	{
		*ast = new;
		return ;
	}
	(*ast)->next_left = new;
}

void	ft_astadd_right(t_ast **ast, t_ast *new)
{
	if (ast == NULL)
		return ;
	if (*ast == NULL)
	{
		*ast = new;
		return ;
	}
	(*ast)->next_right = new;
}

t_ast	*ft_astnew(t_list *lst_token, int len)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->lst_token = lst_token;
	node->lst_len = len;
	node->next_left = NULL;
	node->next_right = NULL;
	return (node);
}
