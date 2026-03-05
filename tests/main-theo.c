#include "minishell.h"	

void	safe_readline(char* input)
{
	int	saved_stdout;

	if (isatty(STDIN_FILENO))
		input = readline("\e[0;36mMinishell> \e[0;33m");
	else
	{
		saved_stdout = dup(STDOUT_FILENO);
		dup2(open("/dev/null", O_WRONLY), STDOUT_FILENO);
		input = readline(NULL);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	init_minishell(&minishell, envp);
	if (!fill_env(&minishell.env, envp))
		return (1);
	// jai limpression que ca avait une raison mais je sais plus pourquoi
	//write (1, "\033[H\033[2J", 8);
	g_sig = 0;
	init_signals();
	while (1)
	{
		safe_readline(minishell.input);
		if (minishell.input == NULL)
			break ;
		if (ft_strlen(minishell.input) == 0)
		{
			free (minishell.input);
			continue;
		}
		if (isatty(STDIN_FILENO))
			add_history(minishell.input);
		tokenizer(minishell.input, &minishell);
		if (syntax_checker(&minishell))
		{
			if (!convert_all_heredoc(&minishell))
			{
				free_token_list(&minishell.tokens_list);
				free(minishell.input);
				continue ;
			}
			minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
			create_ast(minishell.ast);
			rl_reset_terminal(NULL);
			ast_descent(minishell.ast, &minishell);
			free_ast(minishell.ast);
		}
		minishell.previous_last_status=minishell.last_status;
		free_token_list(&minishell.tokens_list);
		free(minishell.input);
	}
	rl_clear_history();
	free_minishell(&minishell);
	return (0);
}

