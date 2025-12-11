#include "minishell.h"

int	main(void)
{
	t_minishell	minishell;
	t_ast		*node; 		

	minishell.tokens_list = NULL;

	tokenizer("a&& ((b && c))", &minishell);
	syntax_checker(&minishell);
	print_token(&minishell);
	minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
	create_ast(minishell.ast);
	ft_printf("\n AST\n\n");
	print_ast(minishell.ast);
	free_token_list(&minishell.tokens_list);
}