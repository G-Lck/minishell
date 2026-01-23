#include "minishell.h"

static void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	exec_executable(t_ast *node, t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	char *cmd_path;
	char **args;


	args = node->exec_token;
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
		cmd_path = find_command(node, &status, minishell->envp);
	if (status == OK)
	{
		ft_printf("Command found at: %s\n", cmd_path);
		if (execve(cmd_path, args, minishell->envp) == -1)
		{
			perror(args[0]);
			free_args(args);
			exit(126);
		}
	}
	else
	{
		if (execve(args[0], args, minishell->envp) == -1)
		{
			ft_printf("minishell: %s: command not found\n", args[0]);
			free_args(args);
			exit(127);
		}
		exit(EXIT_FAILURE);
	}
	free_args(args);
	node->exec_status = EXIT_SUCCESS;
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

char **tokens_to_args(t_list *token_list, int len)
{
	t_list *current;
	t_token *token;
	char **args;
	int i;

	if (!token_list)
		return (NULL);
	current = token_list;


	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	current = token_list;
	i = 0;
	while (current && i < len)
	{
		token = (t_token *)current->content;
		if (token && token->literal)
			args[i] = ft_strdup(token->literal);
		else
			args[i] = ft_strdup("");
		current = current->next;
		i++;
	}
	args[len] = NULL;

	return (args);
}

void	ast_descent(t_ast *node, t_minishell *minishell)
{
	char **args;
	if (node->node_type == AND_OP)
	{
		ft_printf("and\n");
		ast_descent (node->next_left, minishell);
		ft_printf("exec_status: %i\n", node->next_left->exec_status);
		if (node->next_left->exec_status == 0)
		{
			ft_printf("valide\n");
			ast_descent(node->next_right, minishell);
			node->exec_status = node->next_right->exec_status;
		}
		else
			node->exec_status = node->next_left->exec_status;
	}
	else if (node->node_type == OR_OP)
	{
		ast_descent(node->next_left, minishell);
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
		ft_printf("la\n");
		exec_pipeline(node, minishell);
		node->exec_status = node->next_left->exec_status;
	}
	else
	{
		//node_preparation(node, minishell);
		//debug_node(node);
		args = tokens_to_args(node->lst_token, node->lst_len);
		node->exec_token = args;
		exec_node(node, minishell);
	}
	return ;
}
