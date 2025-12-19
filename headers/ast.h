# ifndef AST_H
# define AST_H

# include "minishell.h"

typedef struct s_minishell t_minishell;

typedef enum e_node_type
{
	AND_OP = 0,
	OR_OP = 1,
	PIPE_OP = 2,
	CMD = 3
} t_node_type;

typedef struct s_redir
{
	t_token_type	redir_type;
	char			*target;
}	t_redir;

typedef struct s_ast
{
	t_node_type		node_type;
	t_list			*lst_token;
	struct s_ast	*next_left;
	struct s_ast	*next_right;
	t_list			*redirs;
	int				lst_len;
	int				exec_status;
	bool			is_subshell;
} t_ast;

t_ast	*ft_astnew(t_list *lst_token, int len);
void	create_ast(t_ast *node);
void	test_ast(t_minishell *minishell);
void	print_ast(t_ast *node);
void	print_ast_pretty(t_ast *node);

# endif
