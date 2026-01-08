#include "minishell.h"

void	exec_pipeline(t_ast *node)
{

}

void	exec_node(t_ast *node, t_minishell *data)
{
	char	*cmd;
	int		status;

	cmd = find_command(node, &status, data->envp);
	ft_printf("%s ", ((t_token*)node->lst_token->content)->literal);
	if (cmd != NULL)
	{
		if (status == 0)
			ft_printf("Is directory\n");
		else if (status == -1)
			ft_printf("Not executable\n");
		else
			ft_printf("Excutable !\n");
	}
	if (!cmd)
		ft_printf("Command not found\n");
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
