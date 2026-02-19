#include "minishell.h"

void	free_tab(char **tab)
{
	int	index;

	index = 0;
	while (tab[index])
	{
		free (tab[index]);
		index ++;
	}
	free(tab);
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
		free_env(&minishell->env);
		minishell->env = NULL;
	}
	if (minishell->current_dir)
	{
		free(minishell->current_dir);
		minishell->current_dir = NULL;
	}
}