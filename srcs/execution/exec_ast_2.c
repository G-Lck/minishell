#include "minishell.h"

void	exec_node(t_ast *node, t_minishell *data)
{
	pid_t	pid;
	int		status;

	// Fork pour exécuter la commande
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		node->exec_status = 1;
		return ;
	}

	if (pid == 0)
	{
		simple_command_exec(node, data);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			node->exec_status = 1;
		}
		else
		{
			if (WIFEXITED(status))
				node->exec_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				node->exec_status = 128 + WTERMSIG(status);
		}
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
