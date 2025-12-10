# include "ast.h"

void	ft_astprint(t_ast *ast)
{
	ft_printf(" %s\n", ast->token);
	if (ast->next_left != NULL)
	{
		ft_printf("l");
		ft_astprint(ast->next_left);
		ft_printf("r");
		ft_astprint(ast->next_right);
	}
	return ;
}
int	is_op(t_token_type t)
{
	if (t == AND)
		return (1);
	return (0);
}

t_ast	*ft_astnew(t_token *token_content, int type)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = token_content;
	node->next_left = NULL;
	node->next_right = NULL;
	return (node);
}

void	create_ast(t_ast **node)
{
	t_token	*token;
	int		i;
	t_ast	*node_left;
	t_ast	*node_right;
	int		len;
	t_token_type t;

	t = 1;
	token = (*node)->token;
	len = ft_lstsize(token);
	i = 0;
	while(i < len)
	{
		if (is_op(t, ))
		{
			(*node)->token = strndup(str + i, 1); // devient operateur
			node_left = ft_astnew(strndup(str, i), 1); // cree gauche
			node_right = ft_astnew(str + i + 1, 1); // cree droite
			(*node)->next_left = node_left;
			(*node)->next_right = node_right;
			create_ast(&node_left);
			create_ast(&node_right);
		}
		i++;
	}
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
