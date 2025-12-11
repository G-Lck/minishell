#include "minishell.h"



int	main(int argc, char *argv[])
{
	t_minishell	minishell;

	minishell.tokens_list = NULL;

	while (1)
	{
		minishell.input = readline("\e[0;36m\nMinihell > \e[0;33m");
		tokenizer(minishell.input, &minishell);
		if (syntax_checker(&minishell))
			print_token(&minishell);
		free_token_list(&minishell.tokens_list);
	}
	return (0);
}
