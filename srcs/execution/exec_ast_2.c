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

void	print_token_list(t_list *redir_lst, t_list *exec_lst)
{
	t_redir	*redir;
	t_token *token;

	ft_printf("-----------\n");
	while (exec_lst)
	{
		token = exec_lst->content;
		ft_printf("[%s] ->", token->literal);
		exec_lst = exec_lst->next;
	}
	ft_printf("\n");
	while (redir_lst)
	{
		redir = redir_lst->content;
		ft_printf("redir : %d : %s\n", redir->redir_type, redir->target);
		redir_lst = redir_lst->next;
	}
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
		print_token_list(node->redirs, node->exec_lst);
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
