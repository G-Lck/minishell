# include "../ast.h"

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