#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	free(minishell->current_dir);
	free_env(&minishell->env);
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

int    main(int argc, char *argv[], char *envp[])
{
    t_minishell    minishell;

    minishell.tokens_list = NULL;
    minishell.envp = envp;
    minishell.current_dir = ft_calloc(sizeof(char), 100);
    getcwd(minishell.current_dir, 100);
    minishell.env = NULL;

    if (!fill_env(&minishell.env, envp))
        return (1);
    write (1, "\033[H\033[2J", 8);
    while (1)
    {
        minishell.input = readline("\e[0;36mminishell> \e[0;33m");
        if (ft_strlen(minishell.input) == 0)
            continue;
        tokenizer(minishell.input, &minishell);
        if (syntax_checker(&minishell))
        {
            minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
            create_ast(minishell.ast);
            //rl_reset_terminal(NULL);
            ast_descent(minishell.ast, &minishell);
        }
		minishell.previous_last_status=minishell.last_status;
        free_ast(minishell.ast);
        free_token_list(&minishell.tokens_list);
    }
    free_minishell(&minishell);
    return (0);
}