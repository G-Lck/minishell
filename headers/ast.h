# ifndef AST_H
# define AST_H

# include "minishell.h"

typedef struct s_ast
{
	struct t_token	*token;
	struct s_ast	*next_left;
	struct s_ast	*next_right;
} t_ast;

# endif
