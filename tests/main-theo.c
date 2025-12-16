#include "minishell.h"

// void	ast_descent(t_test *node)
// {
// 	if (node->node_type == AND_OP || node->node_type == OR_OP || node->node_type == PIPE_OP)
// 		ast_descent (node->left);
// 	else
// 	{
// 		ft_printf("(%s)", node->literal);
// 		return ;
// 	}

// 	if (node->node_type == AND_OP)
// 	{
// 		if (node->left->exec_status == 0)
// 		{
// 			ast_descent(node->right);
// 			node->exec_status = node->right->exec_status;
// 		}
// 		else
// 			node->exec_status = node->left->exec_status;
// 	}
// 	else if (node->node_type == OR_OP)
// 	{
// 		if (node->left->exec_status != 0)
// 		{
// 			ast_descent(node->right);
// 			node->exec_status = node->right->exec_status;
// 		}
// 		else
// 			node->exec_status = node->left->exec_status;
// 	}
// 	else if (node->node_type == PIPE_OP)
// 	{
// 		ast_descent(node->right);
// 		node->exec_status = node->left->exec_status;
// 	}
// 	return ;
// }

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
			print_token(&minishell);
		free_token_list(&minishell.tokens_list);
	}
	return (0);

	// t_test	head;
	// t_test second_level_left;
	// t_test second_level_right;
	// t_test third_level_left;
	// t_test third_level_right;

	// head.node_type = PIPE_OP;
	// second_level_left.node_type = AND_OP;
	// second_level_right.node_type = CMD;
	// third_level_left.node_type = CMD;
	// third_level_right.node_type = CMD;

	// head.literal = "||";
	// second_level_right.literal = "echo c";
	// third_level_left.literal = "echo a";
	// third_level_right.literal = "echo b";

	// head.exec_status = 0;
	// second_level_left.exec_status = 0;
	// third_level_left.exec_status = 1;
	// third_level_right.exec_status = 0;
	// second_level_right.exec_status = 0;

	// head.left = &second_level_left;
	// head.right = &second_level_right;
	// second_level_left.left = &third_level_left;
	// second_level_left.right = &third_level_right;

	// ast_descent(&head);
}
