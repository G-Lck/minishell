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

void	exec_executable(t_ast *node, t_minishell *minishell, bool in_pipeline)
{
	pid_t	pid;
	int		status;
	char *cmd_path;
	char **args;

	args = node->exec_token;

	if (in_pipeline)
	{
		cmd_path = find_command(node, &status, minishell);
		if (status == OK)
		{
			if (execve(cmd_path, args, minishell->envp) == -1)
			{
				perror(args[0]);
				//free_args(args);
				exit(126);
			}
		}
		else
		{
			if (execve(args[0], args, minishell->envp) == -1)
			{
				ft_fprintf(STDERR_FILENO,
					"minishell: %s: command not found\n", args[0]);
				//free_args(args);
				exit(127);
			}
			exit(EXIT_FAILURE);
		}
		//free_args(args);
		exit(EXIT_FAILURE);
	}

	// Not in pipeline - do normal fork/exec
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		minishell->last_status = 1;
		return ;
	}

	if (pid == 0)
	{
		apply_redirections(node);
		cmd_path = find_command(node, &status, minishell);
		if (status == OK)
		{
			if (execve(cmd_path, args, minishell->envp) == -1)
			{
				perror(args[0]);
				//free_args(args);
				exit(126);
			}
		}
		else
		{
			if (execve(args[0], args, minishell->envp) == -1)
			{
				ft_fprintf(STDERR_FILENO,
					"minishell: %s: command not found\n", args[0]);
				//free_args(args);
				exit(127);
			}
			exit(EXIT_FAILURE);
		}
		//free_args(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			minishell->last_status = 1;
		}
		else
		{
			if (WIFEXITED(status))
				minishell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				minishell->last_status = 128 + WTERMSIG(status);
		}
	}
}

int	ft_lstlen(t_list *lst)
{
	int i;

	i = 0;
	while(lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char **tokens_to_args(t_list *token_list)
{
	t_list *current;
	t_token *token;
	char **args;
	int i;
	int len;

	if (!token_list)
		return (NULL);
	current = token_list;

	len = ft_lstlen(token_list);

	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	current = token_list;
	i = 0;
	while (current)
	{
		token = (t_token *)current->content;
		if (token && token->literal)
			args[i] = ft_strdup(token->literal);
		else
			args[i] = ft_strdup("");
		current = current->next;
		i++;
	}
	args[i] = NULL;

	return (args);
}

void	ast_descent(t_ast *node, t_minishell *minishell)
{
	if (node->node_type == AND_OP)
	{
		ast_descent (node->next_left, minishell);
		if (minishell->last_status == 0)
			ast_descent(node->next_right, minishell);
	}
	else if (node->node_type == OR_OP)
	{
		ast_descent(node->next_left, minishell);
		if (minishell->last_status != 0)
			ast_descent(node->next_right, minishell);
	}
	else if (node->node_type == PIPE_OP)
		exec_pipeline(node, minishell);
	else
	{
		command_preparation(node, minishell);
		node->exec_token = tokens_to_args(node->exec_lst);
		exec_node_no_pipeline(node, minishell);
	}
	return ;
}
