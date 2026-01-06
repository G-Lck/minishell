#include "minishell.h"

void	exec_pipeline(t_ast *node)
{
	
}

void	exec_node(t_ast *node)
{
	
}

void	ast_descent(t_ast *node)
{
	if (node->node_type == AND_OP || node->node_type == OR_OP || node->node_type == PIPE_OP)
		ast_descent (node->next_left);
	else
	{
		if (!node->is_subshell)
			exec_node(node);
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