#include "minishell.h"

sig_atomic_t g_sig;

void	free_minishell(t_minishell *minishell)
{
	free (minishell->current_dir);
	free_env2(&minishell->env);
}

void sig_handler(int sig)
{
	if (sig == SIGINT) {
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_printf("%d", sig);
}

void init_signals(void){
	struct sigaction sig;

	sig.sa_handler = sig_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, (struct sigaction *)NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	minishell.tokens_list = NULL;
	minishell.envp = envp;
	minishell.current_dir = ft_calloc(sizeof(char), 100);
	minishell.current_dir = getcwd(minishell.current_dir, 100);
	minishell.env = NULL;

	if (!fill_env(&minishell.env, envp))
		return (1);
	write (1, "\033[H\033[2J", 8);
	while (1)
	{
		init_signals();
		minishell.input = readline("\e[0;36mMinishell > \e[0;33m");
		if (minishell.input == NULL || ft_strlen(minishell.input) == 0)
			continue;
		tokenizer(minishell.input, &minishell);
		if (syntax_checker(&minishell))
		{
			minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
			create_ast(minishell.ast);
			//rl_reset_terminal(NULL);
			ast_descent(minishell.ast, &minishell);
		}
		free_ast(minishell.ast);
		free_token_list(&minishell.tokens_list);
	}
	free_minishell(&minishell);
	return (0);
}
