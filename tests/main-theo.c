#include "minishell.h"

typedef enum e_node_type
{
	OPERATOR,
	CMD
} node_type;

typedef struct s_test
{
	struct s_test	*right;
	struct s_test	*left;
	node_type		node_type;
	char			*literal;
	int fail;
} t_test;

void	ast_descent(t_test node, int exit)
{
	if (node.node_type == OPERATOR)
	{
		ast_descent (*node.left, 0);
	}
	else
	{
		ft_printf("(%s)", node.literal);
		if (node.fail == 1)
			exit = 1;
		return ;
	}
	if (exit == 0)
		ast_descent(*node.right, 0);
}

int	main(int argc, char *argv[])
{
	// t_minishell	minishell;

	// minishell.tokens_list = NULL;

	// write (1, "\033[H\033[2J", 8);
	// while (1)
	// {
	// 	minishell.input = readline("\e[0;36m\nMinihell > \e[0;33m");
	// 	tokenizer(minishell.input, &minishell);
	// 	if (syntax_checker(&minishell))
	// 		print_token(&minishell);
	// 	free_token_list(&minishell.tokens_list);
	// }
	// return (0);

	t_test	head;
	t_test second_level_left;
	t_test second_level_right;
	t_test third_level_left;
	t_test third_level_right;

	head.node_type = OPERATOR;
	second_level_left.node_type = OPERATOR;
	second_level_right.node_type = CMD;
	third_level_left.node_type = CMD;
	third_level_right.node_type = CMD;

	head.literal = "||";
	second_level_right.literal = "echo c";
	third_level_left.literal = "echo a";
	third_level_right.literal = "echo b";

	head.fail = 0;
	second_level_left.fail = 0;
	third_level_left.fail = 1;
	third_level_right.fail = 0;
	second_level_right.fail = 0;

	head.left = &second_level_left;
	head.right = &second_level_right;
	second_level_left.left = &third_level_left;
	second_level_left.right = &third_level_right;

	ast_descent(head, 0);
}
