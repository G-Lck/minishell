# include "ast.h"

void	ft_astadd_back_left(t_ast **last, t_ast *new)
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
	last->next = new;
}

t_ast	*ft_astnew(char *content, int type)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->raw = content;
	node->next_left = NULL;
	node->next_right = NULL;
	return (node);
}
