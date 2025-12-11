#include "minishell.h"

int	main(void)
{
	t_minishell	minishell;
	t_ast		*node; 		

	minishell.tokens_list = NULL;

	tokenizer("a&&b", &minishell);
	syntax_checker(&minishell);
	print_token(&minishell);
	minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
	test_ast(&minishell);
	free_token_list(&minishell.tokens_list);
}