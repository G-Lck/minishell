#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_minishell	minishell;

	minishell.tokens_list = NULL;

	tokenizer("&& || | (hello && bonj'\"hey\"'our) < << > >>", &minishell);
	return (0);
}
