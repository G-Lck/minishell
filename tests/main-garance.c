#include "minishell.h"

int	main(void)
{
	t_minishell	minishell;
	t_ast		*node;

	minishell.tokens_list = NULL;

	tokenizer("(a b&& (c | f))", &minishell);
	syntax_checker(&minishell);
	print_token(&minishell);
	minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
	create_ast(minishell.ast);
	ft_printf("\n AST (OMG)\n\n");
	print_ast_pretty(minishell.ast);
	ft_printf("\nBegin exec\n\n");
	exec_ast(minishell.ast);
	free_token_list(&minishell.tokens_list);
}
