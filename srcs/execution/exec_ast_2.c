#include "minishell.h"

void	exec_pipeline(t_ast *node)
{

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
		ft_printf("Command not found\n");
	else if (status == IS_DIRECTORY)
		ft_printf("Is directory\n");
	else if (status == PERMISSION_DENIED)
		ft_printf("Permission denied\n");
	status = 0;
}

void	ast_descent(t_ast *node, t_minishell *data)
{
	if (node->node_type == AND_OP || node->node_type == OR_OP || node->node_type == PIPE_OP)
		ast_descent (node->next_left, data);
	else
	{
		if (!node->is_subshell)
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
