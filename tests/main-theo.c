#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	minishell.tokens_list = NULL;
	minishell.envp = envp;
	minishell.current_dir = ft_calloc(sizeof(char), 100);
	minishell.current_dir = getcwd(minishell.current_dir, 100);
	minishell.env = NULL;
	if (!feel_env(&minishell.env, envp))
		return (1);
	// char *str = "bonjour ca\"\'$HOME\'\" va";
	// str = expand_variables(str, minishell.env);
	// printf("%s", str);
	write (1, "\033[H\033[2J", 8);
	ft_printf("%s\n", minishell.current_dir);
	while (1)
	{
		minishell.input = readline("\e[0;36m\nMinihell > \e[0;33m");
		tokenizer(minishell.input, &minishell);
		if (syntax_checker(&minishell))
		{
			minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
			create_ast(minishell.ast);
			print_ast_pretty(minishell.ast);
			//rl_reset_terminal(NULL);
			ast_descent(minishell.ast, &minishell);
		}
		//Free les lst_token et les redirs dans chaque node
		free_ast(minishell.ast);
		free_token_list(&minishell.tokens_list);
	}
	return (0);
}
