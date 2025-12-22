#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_minishell	minishell;

	minishell.tokens_list = NULL;

	write (1, "\033[H\033[2J", 8);
	while (1)
	{
		minishell.input = readline("\e[0;36m\nMinihell > \e[0;33m");
		tokenizer(minishell.input, &minishell);
		if (syntax_checker(&minishell))
		{
			minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
			create_ast(minishell.ast);
			print_ast_pretty(minishell.ast);
			ast_descent(minishell.ast);
		}
		free_ast(minishell.ast);
		free_token_list(&minishell.tokens_list);
	}
	return (0);
}
