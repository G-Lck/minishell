#include "minishell.h"
#include "pipeline.h"

void	exec_pipeline(t_ast *node, t_minishell *data)
{
	t_pipeline	*pipeline;

	pipeline = init_pipeline_data(node);
	if (!pipeline)
		return ;

	if (create_pipes(pipeline) == -1)
	{
		cleanup_pipeline_data(pipeline);
		return ;
	}

	execute_pipeline_commands(node, data, pipeline);

	// Fermer les pipes dans le parent APRÈS avoir créé tous les enfants
	close_all_pipes(pipeline->pipes_tab, pipeline->total_pipe);

	wait_for_pipeline_completion(pipeline, data);
	cleanup_pipeline_data(pipeline);
}

int	count_pipeline_commands(t_ast *node)
{
	int	count;

	count = 1;
	while (node && node->node_type == PIPE_OP)
	{
		count++;
		node = node->next_right;
	}
	return (count);
}

int	get_input_redirection(t_ast *node)
{
	t_list	*current;
	t_redir	*redir;
	int		fd;

	if (!node || !node->redirs)
		return (-1);

	current = node->redirs;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->redir_type == REDIR_IN)
		{
			fd = open(redir->target, O_RDONLY);
			if (fd == -1)
			{
				perror(redir->target);
				exit(EXIT_FAILURE);
			}
			return (fd);
		}
		current = current->next;
	}
	return (-1);
}

int	get_output_redirection(t_ast *node)
{
	t_list	*current;
	t_redir	*redir;
	int		fd;

	if (!node || !node->redirs)
		return (-1);

	current = node->redirs;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->redir_type == REDIR_OUT)
		{
			fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(redir->target);
				exit(EXIT_FAILURE);
			}
			return (fd);
		}
		else if (redir->redir_type == APPEND)
		{
			fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(redir->target);
				exit(EXIT_FAILURE);
			}
			return (fd);
		}
		current = current->next;
	}
	return (-1);
}

int	**create_pipes_tab(int pipe_count)
{
	int	**pipes_tab;
	int	i;

	if (pipe_count <= 0)
		return (NULL);

	pipes_tab = malloc(sizeof(int *) * pipe_count);
	if (!pipes_tab)
		return (NULL);

	i = 0;
	while (i < pipe_count)
	{
		pipes_tab[i] = malloc(sizeof(int) * 2);
		if (!pipes_tab[i] || pipe(pipes_tab[i]) == -1)
		{
			cleanup_pipes_tab(pipes_tab, i);
			return (NULL);
		}
		i++;
	}

	return (pipes_tab);
}

void	cleanup_pipes_tab(int **pipes_tab, int pipe_count)
{
	int	i;

	if (!pipes_tab)
		return ;

	i = 0;
	while (i < pipe_count)
	{
		if (pipes_tab[i])
			free(pipes_tab[i]);
		i++;
	}
	free(pipes_tab);
}

t_pipeline	*init_pipeline_data(t_ast *node)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
	{
		perror("Failed to allocate pipeline data");
		return (NULL);
	}

	pipeline->total_cmds = count_pipeline_commands(node);
	pipeline->total_pipe = pipeline->total_cmds - 1;
	pipeline->pipes_tab = NULL;
	pipeline->pids = NULL;

	if (pipeline->total_cmds > 0)
	{
		pipeline->pids = malloc(sizeof(pid_t) * pipeline->total_cmds);
		if (!pipeline->pids)
		{
			perror("Failed to allocate PIDs array");
			free(pipeline);
			return (NULL);
		}
	}

	return (pipeline);
}

int	create_pipes(t_pipeline *pipeline)
{
	if (pipeline->total_pipe <= 0)
		return (0);

	pipeline->pipes_tab = create_pipes_tab(pipeline->total_pipe);
	if (!pipeline->pipes_tab)
		return (-1);

	return (0);
}

void	cleanup_pipeline_data(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;

	if (pipeline->pipes_tab)
		cleanup_pipes_tab(pipeline->pipes_tab, pipeline->total_pipe);

	if (pipeline->pids)
		free(pipeline->pids);

	free(pipeline);
}

void	execute_pipeline_commands(t_ast *node, t_minishell *data, t_pipeline *pipeline)
{
	int	cmd_index;

	cmd_index = 0;
	execute_pipeline_recursive(node, data, pipeline, &cmd_index);
}

void	execute_pipeline_recursive(t_ast *node, t_minishell *data, t_pipeline *pipeline, int *cmd_index)
{
	if (!node)
		return ;

	if (node->node_type == CMD)
	{
		execute_single_command(node, data, pipeline, *cmd_index);
		(*cmd_index)++;
		return ;
	}

	if (node->node_type == PIPE_OP)
	{
		execute_pipeline_recursive(node->next_left, data, pipeline, cmd_index);
		execute_pipeline_recursive(node->next_right, data, pipeline, cmd_index);
	}
}

void	execute_single_command(t_ast *node, t_minishell *minishell,
	t_pipeline *pipeline, int cmd_index)
{
	char **args;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		return ;
	}

	if (pid == 0)
	{
		setup_pipe_redirections(pipeline->pipes_tab, cmd_index, pipeline->total_cmds, node);

		// Fermer SEULEMENT les pipes non utilisés par ce processus
		close_unused_pipes(pipeline->pipes_tab, pipeline->total_pipe, cmd_index);

		// ✅ Préparer la commande AVANT tokens_to_args
		command_preparation(node, minishell);
		args = tokens_to_args(node->exec_lst);
		node->exec_token = args;
		exec_node(node, minishell);

		// Dans un pipeline, le processus enfant DOIT exit
		// Si c'était un builtin, exec_node a fait return après avoir mis à jour minishell->last_status
		// Si c'était une commande externe, exec_executable a déjà fait exit() dans l'enfant
		// Donc on arrive ici seulement pour les builtins :
		exit(minishell->last_status);
	}
	else
	{
		pipeline->pids[cmd_index] = pid;
	}
}

void	setup_pipe_redirections(int **pipes_tab, int cmd_index,
	int total_commands, t_ast *node)
{
	int	input_fd;
	int	output_fd;

	input_fd = get_input_redirection(node);

	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input file failed");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
	else if (cmd_index > 0)
	{
		if (dup2(pipes_tab[cmd_index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 pipe input failed");
			exit(EXIT_FAILURE);
		}
	}

	output_fd = get_output_redirection(node);
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output file failed");
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
	else if (cmd_index < total_commands - 1)
	{
		if (dup2(pipes_tab[cmd_index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout pipe failed");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_all_pipes(int **pipes_tab, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipes_tab[i])
		{
			close(pipes_tab[i][0]);
			close(pipes_tab[i][1]);
		}
		i++;
	}
}

void	close_unused_pipes(int **pipes_tab, int pipe_count, int cmd_index)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipes_tab[i])
		{
			// Ne pas fermer le pipe d'entrée de ce processus
			if (i != cmd_index - 1 || cmd_index == 0)
				close(pipes_tab[i][0]);

			// Ne pas fermer le pipe de sortie de ce processus
			if (i != cmd_index)
				close(pipes_tab[i][1]);
		}
		i++;
	}
}

void	wait_for_pipeline_completion(t_pipeline *pipeline, t_minishell *minishell)
{
	int	status;
	int	i;
	pid_t	rightmost_pid;
	int	rightmost_status;

	// Le PID de la commande la plus à droite est le dernier dans le tableau
	rightmost_pid = pipeline->pids[pipeline->total_cmds - 1];
	rightmost_status = 0;

	i = 0;
	while (i < pipeline->total_cmds)
	{
		if (waitpid(pipeline->pids[i], &status, 0) == -1)
		{
			perror("waitpid failed");
		}
		else
		{
			// Si c'est la commande la plus à droite, capturer son code d'erreur
			if (pipeline->pids[i] == rightmost_pid)
			{
				if (WIFEXITED(status))
					rightmost_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					rightmost_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}

	// Le code d'erreur du pipeline est celui de la commande la plus à droite
	minishell->last_status = rightmost_status;
}
