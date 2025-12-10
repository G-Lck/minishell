#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_minishell	minishell;

	minishell.tokens_list = NULL;

	tokenizer("&&(&&(hello&&     bonj'\"hey\"'our)) bonjour ||", &minishell);
	syntax_checker(&minishell);
	print_token(&minishell);
	free_token_list(&minishell.tokens_list);
	return (0);
}