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

void	print_token_list(t_list *list)
{
	t_redir	*redir;

	while (list)
	{
		redir = list->content;
		ft_printf("redir : %d : %s\n", redir->redir_type, redir->target);
		list = list->next;
	}
}

void	debug_node(t_ast *node)
{
	int	index;

	index = 0;
	ft_printf("\n-----------\n");
	while (node->exec_token[index])
	{
		ft_printf("%s -> ", node->exec_token[index]);
		index ++;
	}
	ft_printf("\n");
	print_token_list(node->redirs);
	ft_printf("-----------\n");
}

void	ast_descent(t_ast *node, t_minishell *minishell)
{
	if (node->node_type == AND_OP || node->node_type == OR_OP)
		ast_descent (node->next_left, minishell);
	else if (node->node_type == PIPE_OP)
	{
		exec_pipeline(node, minishell);
		return ;
	}
	else
	{
		node_preparation(node, minishell);
		//debug_node(node);
		//simple_command_exec(node, minishell);
		return ;
	}
	if (node->node_type == AND_OP)
	{
		if (node->next_left->exec_status == 0)
		{
			ast_descent(node->next_right, minishell);
			node->exec_status = node->next_right->exec_status;
		}
		else
			node->exec_status = node->next_left->exec_status;
	}
	else if (node->node_type == OR_OP)
	{
		if (node->next_left->exec_status != 0)
		{
			ast_descent(node->next_right, minishell);
			node->exec_status = node->next_right->exec_status;
		}
		else
			node->exec_status = node->next_left->exec_status;
	}
	else if (node->node_type == PIPE_OP)
	{
		ast_descent(node->next_right, minishell);
		node->exec_status = node->next_left->exec_status;
	}
	return ;
}
