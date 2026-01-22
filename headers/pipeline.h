#ifndef PIPELINE_H
# define PIPELINE_H

typedef struct s_pipeline
{
	int			**pipes_tab;
	int			total_cmds;
	int			total_pipe;
	pid_t		*pids;
}	t_pipeline;

t_pipeline		*init_pipeline_data(t_ast *node);
int				create_pipes(t_pipeline *pipeline);
void			execute_pipeline_commands(t_ast *node, t_minishell *data, t_pipeline *pipeline);
void			execute_pipeline_recursive(t_ast *node, t_minishell *data, t_pipeline *pipeline, int *cmd_index);
void			execute_single_command(t_ast *node, t_minishell *data, t_pipeline *pipeline, int cmd_index);
void			setup_pipe_redirections(int **pipes_tab, int cmd_index, int total_commands, t_ast *node);
void			close_all_pipes(int **pipes_tab, int pipe_count);
void			wait_for_pipeline_completion(t_pipeline *pipeline, t_ast *node);
void			cleanup_pipeline_data(t_pipeline *pipeline);
void			cleanup_pipes_tab(int **pipes_tab, int pipe_count);
int				**create_pipes_tab(int pipe_count);
int				count_pipeline_commands(t_ast *node);
int				get_input_redirection(t_ast *node);
int				get_output_redirection(t_ast *node);

#endif
