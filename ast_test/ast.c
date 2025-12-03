# include "ast.h"

void	ft_astprint(t_ast *ast)
{
	printf(" %s\n", ast->raw);
	if (ast->next_left != NULL)
	{
		printf("l");
		ft_astprint(ast->next_left);
		printf("r");
		ft_astprint(ast->next_right);
	}
	return ;
}
int	is_in(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
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

void	create_ast(t_ast **node)
{
	char	*str;
	int		i;
	t_ast	*node_left;
	t_ast	*node_right;
	int		len;

	str = (*node)->raw;
	len = strlen(str);
	while(str[i])
	{
		if (is_in(str[i], "*+_/"))
		{
			(*node)->raw = strndup(str + i, 1); // devient operateur
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
int	main(int argc, char **argv)
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
		printf("error");
		return (0);
	}
	node = ft_astnew(argv[1], 0);
	create_ast(&node);
	ft_astprint(node);

}
