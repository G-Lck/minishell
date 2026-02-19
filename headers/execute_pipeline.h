#ifndef EXECUTE_PIPELINE_H
# define EXECUTE_PIPELINE_H

# include <sys/types.h>

typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;

typedef struct s_pipeline
{
	int			**pipes_tab;
	int			total_cmds;
	int			total_pipe;
	pid_t		*pids;
}	t_pipeline;

void	exec_pipeline(t_ast *node, t_minishell *data);
void	apply_redirections(t_ast *node);
int		apply_redirections_safe(t_ast *node);

#endif
