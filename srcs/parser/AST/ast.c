# include "minishell.h"

/*void	ft_astprint(t_minishell *minishell)
{
	t_ast	*ast;
	t_token	*token;
	t_list	*lst_token;

	ast = minishell->ast;
	lst_token = ast->lst_token;
	token = lst_token->content;
	ft_printf(" %s\n", token->literal);
	if (ast->next_left != NULL)
	{
		ft_printf("l");
		ft_astprint(ast->next_left);
		ft_printf("r");
		ft_astprint(ast->next_right);
	}
	return ;
}*/

/*t_list *ft_lstextract(t_list *lst, int position)
{
	int	i;
//ooooooooooooo
	i = 0;
	if (!lst)
		return (NULL);
	while(i < position)
	{
		lst = lst->next;
		i++;
	}
	lst->next = NULL;
	return (lst);
}*/

/*t_list	*ft_lstgoto(t_list *lst, int position)
{
	int i;

	i = 0;
	while (i < position)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}*/


/*t_list *ft_lstcut(t_list *lst, int position)
{
	int i;
	t_list	*temp;

	temp = lst;
	i = 0;
	while (i < position)
	{
		lst = lst->next;
		i++;
	}
	lst->next = NULL;
	return (temp);
}*/

int	is_op(t_token_type t)
{
	if (t == AND || t == OR || t == PIPE)
		return (1);
	return (0);
}

void	create_ast(t_ast *node)
{
	int		i;
	t_list	*lst_token;
	t_token	*token;
	t_ast	*node_left;
	t_ast	*node_right;

	ft_printf("enter create_ast()\n");
	lst_token = node->lst_token;
	i = 0;
	while(i < node->lst_len - 1)
	{
		ft_printf("i: %i\n", i);
		ft_printf("len: %i\n", node->lst_len);
		token = lst_token->content;
		//print_token(lst_token);
		if (is_op(token->type))
		{
			ft_printf("op\n");
			node_left = ft_astnew(node->lst_token, i); // cree gauche
			node_left->lst_len = i;
			node_right = ft_astnew(lst_token->next, i); // cree droite
			node_right->lst_len = node->lst_len - i - 1;
			node->lst_token = lst_token;
			node->lst_len = 1;
			node->next_left = node_left;
			node->next_right = node_right;
			create_ast(node_left);
			create_ast(node_right);
		}
		lst_token = lst_token->next;
		i++;
	}
	return ;
}

void	test_ast(t_minishell *minishell)
{
	t_ast	*node;
	t_list	*lst_token;
	t_token	*token;

	node = minishell->ast;
	lst_token = node->lst_token;

	ft_printf("ici\n");
	token = lst_token->content;
	ft_printf("ici\n");
	ft_printf("token: %s\n", (token->literal));

	return ;
}



/*int	main(int argc, char **argv)
{
	int		i;
	t_ast	*node;
	t_ast	*node_left;
	t_ast	*node_right;
	int p;

	p = 0;
	i = 0;
	if (argc != 2)
	{
		ft_printf("error");
		return (0);
	}
	node = ft_astnew(argv[1], 0);
	create_ast(&node);
	ft_astprint(node);

}*/
