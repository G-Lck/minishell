/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_PIPELINE_H
# define EXECUTE_PIPELINE_H

# include <sys/types.h>

typedef struct s_ast		t_ast;
typedef struct s_minishell	t_minishell;

typedef struct s_pipeline
{
	int			**pipes_tab;
	int			total_cmds;
	int			total_pipe;
	pid_t		*pids;
}	t_pipeline;

/* pipeline_init.c */
t_pipeline	*init_pipeline(t_ast *node);

/* pipeline_cleanup.c */
void		cleanup_pipes_tab(int **pipes_tab, int pipe_count);
void		close_all_pipes(int **pipes_tab, int pipe_count);
void		cleanup_pipeline(t_pipeline *pipeline);
void		wait_pipeline(t_pipeline *pipeline, t_minishell *minishell);

/* pipeline_redir.c */
int			open_redir_fd(t_ast *node, t_token_type type);
void		apply_redirections(t_ast *node);
int			apply_redirections_safe(t_ast *node);

/* pipeline_pipe_redir.c */
void		setup_pipe_redirections(int **pipes, int idx,
				int total, t_ast *node);

/* exec_pipeline.c */
void		exec_pipeline(t_ast *node, t_minishell *minishell);

#endif
