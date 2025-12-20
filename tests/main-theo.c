#include "minishell.h"

void	ast_descent(t_ast *node)
{
	if (node->node_type == AND_OP || node->node_type == OR_OP || node->node_type == PIPE_OP)
		ast_descent (node->next_left);
	else
	{
		t_token *token = node->lst_token->content;
		ft_printf("(%s)", token->literal);
		return ;
	}

	if (node->node_type == AND_OP)
	{
		if (node->next_left->exec_status == 0)
		{
			ast_descent(node->next_right);
			node->exec_status = node->next_right->exec_status;
		}
		else
			node->exec_status = node->next_left->exec_status;
	}
	else if (node->node_type == OR_OP)
	{
		if (node->next_left->exec_status != 0)
		{
			ast_descent(node->next_right);
			node->exec_status = node->next_right->exec_status;
		}
		else
			node->exec_status = node->next_left->exec_status;
	}
	else if (node->node_type == PIPE_OP)
	{
		ast_descent(node->next_right);
		node->exec_status = node->next_left->exec_status;
	}
	return ;
}

int	main(int argc, char *argv[])
{
	t_minishell	minishell;

	minishell.tokens_list = NULL;

	write (1, "\033[H\033[2J", 8);
	while (1)
	{
		minishell.input = readline("\e[0;36m\nMinihell > \e[0;33m");
		tokenizer(minishell.input, &minishell);
		if (syntax_checker(&minishell))
		{
			minishell.ast = ft_astnew(minishell.tokens_list, ft_lstsize(minishell.tokens_list));
			create_ast(minishell.ast);
			print_ast_pretty(minishell.ast);
		}
		free_ast(minishell.ast);
		free_token_list(&minishell.tokens_list);
	}
	return (0);
}
