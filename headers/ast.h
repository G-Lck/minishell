# ifndef AST_H
# define AST_H

# include "minishell.h"

typedef struct s_minishell t_minishell;

typedef enum e_node_type
{
	AND_OP,
	OR_OP,
	PIPE_OP,
	CMD
} t_node_type;

typedef struct s_redir
{
	t_token_type	redir_type;
	char			*target;
}	t_redir;

typedef struct s_ast
{
	t_node_type	node_type;
	t_list	*lst_token;
	t_list	*next_left;
	t_list	*next_right;
	t_list	*redirs;
	int		lst_len;
	int		exec_status;
} t_ast;

void	ft_astadd_left(t_ast **ast, t_ast *new);
void	ft_astadd_right(t_ast **ast, t_ast *new);
t_ast	*ft_astnew(t_list *lst_token, int len);
void	create_ast(t_ast *node);
void	test_ast(t_minishell *minishell);
void	print_ast(t_ast *node);

# endif
