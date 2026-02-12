#include "minishell.h"

void	reinit_minishell(t_minishell *minishell)
{
	minishell->tokens_list = NULL;
	minishell->ast = NULL;
	minishell->input = NULL;
	minishell->current_dir = NULL;
	minishell->exit_code = 0;
	// Sauvegarder le last_status comme previous_last_status
	minishell->previous_last_status = minishell->last_status;
	minishell->last_status = 0;
}

void	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->tokens_list = NULL;
	minishell->ast = NULL;
	minishell->input = NULL;
	minishell->envp = envp;
	minishell->env = NULL;
	minishell->current_dir = NULL;
	minishell->exit_code = 0;
	minishell->last_status = 0;
	minishell->previous_last_status = 0;
}

void	cleanup_minishell(t_minishell *minishell)
{
	if (minishell->tokens_list)
	{
		free_token_list(&minishell->tokens_list);
		minishell->tokens_list = NULL;
	}
	if (minishell->ast)
	{
		free_ast(minishell->ast);
		minishell->ast = NULL;
	}
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	if (minishell->env)
	{
		free_env2(&minishell->env);
		minishell->env = NULL;
	}
}

void	process_command(char *input, t_minishell *minishell)
{
	if (tokenizer(input, minishell) == 0)
	{
		ft_printf("Error: tokenization failed\n");
		return;
	}
	//ft_printf("Tokens: ");
	//print_token(minishell);
	//ft_printf("\n");

	if (syntax_checker(minishell) == 0)
	{
		ft_printf("Error: syntax error\n");
		cleanup_minishell(minishell);
		return;
	}

	minishell->ast = ft_astnew(minishell->tokens_list, ft_lstsize(minishell->tokens_list));
	if (!minishell->ast)
	{
		ft_printf("Error: AST creation failed\n");
		cleanup_minishell(minishell);
		return;
	}

	create_ast(minishell->ast);
	//ft_printf("AST: ");
	//print_ast_pretty(minishell->ast);
	//ft_printf("Execution:\n");

	ast_descent(minishell->ast, minishell);

	// Plus besoin de copier exec_status car last_status est mis à jour directement !
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;
	char		*input;


	if (argc != 1 || argv[1])
		return (1);
	//ft_printf("Enter commands to test tokenization -> AST -> execution\n");
	//ft_printf("Type 'q' to quit\n\n");

	init_minishell(&minishell, envp);
	if (!fill_env(&(&minishell)->env, envp))
	{
		ft_printf("Error: failed to initialize environment\n");
		exit(1);
	}
	while (1)
	{
		input = readline("minishell> ");
		if (ft_strncmp(input, "q", 1) == 0)
		{
			free(input);
			break;
		}
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue;
		}
		add_history(input);
		minishell.input = ft_strdup(input);
		process_command(input, &minishell);
		reinit_minishell(&minishell);
		free(input);
	}
	cleanup_minishell(&minishell);
	rl_clear_history();
	ft_printf("Force à toi\n");
	return (0);
}
