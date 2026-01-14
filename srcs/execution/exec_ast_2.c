#include "minishell.h"

void	exec_pipeline(t_ast *node, t_minishell *data)
{
	node_preparation(node->next_left);
	ft_printf("%s\n", ((t_token *)node->next_left->lst_token->content)->literal);
}

void	exec_node(t_ast *node, t_minishell *data)
{
	char	*cmd;
	int		status;

	status = COMMAND_NOT_FOUND;
	cmd = find_command(node, &status, data->envp);
	ft_printf("%s ", ((t_token*)node->lst_token->content)->literal);
	if (status == OK)
		ft_printf("Excutable !\n");
	else if (status == COMMAND_NOT_FOUND)
	{
		node->exec_status = 127;
		ft_printf("Command not found\n");
		return ;
	}
	else if (status == IS_DIRECTORY)
	{
		node->exec_status = 126;
		ft_printf("Is directory\n");
		return ;
	}
	else if (status == PERMISSION_DENIED)
	{
		node->exec_status = 126;
		ft_printf("Permission denied\n");
		return ;
	}
}

void	ast_descent(t_ast *node, t_minishell *data)
{
	if (node->node_type == AND_OP || node->node_type == OR_OP)
		ast_descent (node->next_left, data);
	else if (node->node_type == PIPE_OP)
	{
		exec_pipeline(node, data);
		return ;
	}
	else
	{
		exec_node(node, data);
		return ;
	}

	if (node->node_type == AND_OP)
	{
		if (node->next_left->exec_status == 0)
		{
			ast_descent(node->next_right, data);
			node->exec_status = node->next_right->exec_status;
		}
		else
			node->exec_status = node->next_left->exec_status;
	}
	else if (node->node_type == OR_OP)
	{
		if (node->next_left->exec_status != 0)
		{
			ast_descent(node->next_right, data);
			node->exec_status = node->next_right->exec_status;
		}
		else
			node->exec_status = node->next_left->exec_status;
	}
	else if (node->node_type == PIPE_OP)
	{
		ast_descent(node->next_right, data);
		node->exec_status = node->next_left->exec_status;
	}
	return ;
}
