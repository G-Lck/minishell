/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_execve(t_ast *node, t_minishell *minishell)
{
	int		status;
	char	*cmd_path;
	char	**arg;
	char	**envp;

	arg = node->exec_token;
	envp = env_to_envp(minishell->env);
	cmd_path = find_command(node, &status, minishell);
	if (status == PERMISSION_DENIED)
	{
		ft_fprintf(2, "minishell: %s: permission denied\n", arg[0]);
		clean_exit(minishell, 126);
	}
	if (status == OK && execve(cmd_path, arg, envp) == -1)
	{
		perror(arg[0]);
		clean_exit(minishell, 126);
	}
	if (execve(arg[0], arg, envp) == -1)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", arg[0]);
		clean_exit(minishell, 127);
	}
}

void	try_execve_pipeline(t_ast *node, t_minishell *mini, t_pipeline *p)
{
	int		status;
	char	*cmd_path;
	char	**arg;
	char	**envp;

	arg = node->exec_token;
	envp = env_to_envp(mini->env);
	cmd_path = find_command(node, &status, mini);
	if (status == PERMISSION_DENIED)
	{
		ft_fprintf(2, "minishell: %s: permission denied\n", arg[0]);
		clean_exit_pipeline(mini, p, 126);
	}
	if (status == OK && execve(cmd_path, arg, envp) == -1)
	{
		perror(arg[0]);
		clean_exit_pipeline(mini, p, 126);
	}
	if (execve(arg[0], arg, envp) == -1)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", arg[0]);
		clean_exit_pipeline(mini, p, 127);
	}
}

static void	wait_child(pid_t pid, t_minishell *minishell)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		minishell->status = 1;
	}
	if (WIFEXITED(status))
		minishell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->status = 128 + WTERMSIG(status);
}

void	exec_no_pipeline(t_ast *node, t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		minishell->status = 1;
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		apply_redirections(node);
		try_execve(node, minishell);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait_child(pid, minishell);
		init_signals();
		if (minishell->status == 130)
			ft_printf("\n");
	}
}

void	ast_descent(t_ast *node, t_minishell *minishell)
{
	if (node->node_type == AND_OP)
	{
		ast_descent(node->next_left, minishell);
		if (minishell->status == 0)
			ast_descent(node->next_right, minishell);
	}
	else if (node->node_type == OR_OP)
	{
		ast_descent(node->next_left, minishell);
		if (minishell->status != 0)
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
}
