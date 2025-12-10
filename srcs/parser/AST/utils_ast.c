# include "ast.h"

void	ft_astadd_back_left(t_ast **lst, t_ast *new)
{
	t_ast	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next_left = new;
}

void	ft_astadd_back_right(t_ast **lst, t_ast *new)
{
	t_ast	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next_right = new;
}

t_ast	*ft_astnew(t_token *content, int type)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = content;
	node->next_left = NULL;
	node->next_right = NULL;
	return (node);
}
