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
	signal(SIGINT, sigint_exec);
	signal(SIGQUIT, sigquit_exec);

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		minishell->last_status = 1;
		return ;
	}

	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
		while (waitpid(pid, &status, 0) == -1)
		{
			if (errno == EINTR)
				continue;

			perror("waitpid failed");
			minishell->last_status = 1;
			return;
		}

		if (WIFEXITED(status))
			minishell->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->last_status = 128 + WTERMSIG(status);
		
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
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
		//ft_printf("exec_status: %i\n", minishell->last_status);
		if (minishell->last_status == 0)
		{
			//ft_printf("valide\n");
			ast_descent(node->next_right, minishell);
			// last_status est déjà à jour après next_right
		}
		// sinon on garde le last_status de next_left
	}
	else if (node->node_type == OR_OP)
	{
		ast_descent(node->next_left, minishell);
		if (minishell->last_status != 0)
		{
			ast_descent(node->next_right, minishell);
			// last_status est déjà à jour après next_right
		}
		// sinon on garde le last_status de next_left
	}
	else if (node->node_type == PIPE_OP)
	{
		//ft_printf("la\n");
		exec_pipeline(node, minishell);
		// exec_pipeline devrait déjà mettre à jour minishell->last_status
	}
	else
	{
		command_preparation(node, minishell);
		//debug_node(node);
		node->exec_token = tokens_to_args(node->exec_lst);

		exec_node_no_pipeline(node, minishell);
		// Ne pas écraser last_status si c'était une expansion de $?
		// Pour l'instant on met toujours à jour, mais c'est le vrai problème
	}
	return ;
}
