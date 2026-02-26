#include "minishell.h"

sig_atomic_t g_sig;

void	free_minishell(t_minishell *minishell)
{
	free(minishell->current_dir);
	free_env(&minishell->env);
}

void sigint_exec(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void sigquit_exec(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit (core dumped)\n", 20);
}

void sig_handler(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void init_signals(void)
{
	struct sigaction sig;

	sig.sa_handler = sig_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	minishell->tokens_list = NULL;
// 	minishell->ast = NULL;
// 	minishell->input = NULL;
// 	minishell->envp = envp;
// 	minishell->env = NULL;
// 	minishell->current_dir = NULL;
// 	minishell->exit_code = 0;
// 	minishell->last_status = 0;
// 	minishell->previous_last_status = 0;
// }

void	init_minishell(t_minishell *minishell, char *envp[])
{
	minishell->tokens_list = NULL;
	minishell->ast = NULL;
	minishell->input = NULL;
	minishell->envp = envp;
	minishell->env = NULL;
	minishell->current_dir = ft_calloc(sizeof(char), 100);
	minishell->exit_code = 0;
	minishell->last_status = 0;
	getcwd(minishell->current_dir, 100);
	minishell->previous_last_status = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;
	int			saved_stdout;

	init_minishell(&minishell, envp);

	if (!fill_env(&minishell.env, envp))
		return (1);
	write (1, "\033[H\033[2J", 8);

	while (1)
	{
		init_signals();
		if (isatty(STDIN_FILENO))
			minishell.input = readline("\e[0;36mMinishell> \e[0;33m");
		else
		{
			saved_stdout = dup(STDOUT_FILENO);
			dup2(open("/dev/null", O_WRONLY), STDOUT_FILENO);
			minishell.input = readline(NULL);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
		}
		if (minishell.input == NULL)
			break ;
		if (ft_strlen(minishell.input) == 0)
			continue ;
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
		}
		minishell.previous_last_status=minishell.last_status;
		free_ast(minishell.ast);
		free_token_list(&minishell.tokens_list);
		//rl_on_new_line();
	}
	rl_clear_history();
	free_minishell(&minishell);
	return (0);
}

