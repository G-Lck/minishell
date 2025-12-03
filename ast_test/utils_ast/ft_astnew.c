
# include "../ast.h"

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