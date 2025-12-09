#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_minishell	minishell;

	minishell.tokens_list = NULL;

	tokenizer("&& || | (hello && bonj'\"hey\"'our) < << > >>", &minishell);
	pop_token(0, &minishell.tokens_list);
	print_token(&minishell);
	free_token_list(&minishell.tokens_list);
	return (0);
}