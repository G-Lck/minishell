# ifndef AST_H
# define AST_H

# include "minishell.h"

typedef struct s_minishell t_minishell;

typedef struct s_ast
{
	t_list	*lst_token;
	int		lst_len;
	t_list	*next_left;
	t_list	*next_right;
} t_ast;

void	ft_astadd_left(t_ast **ast, t_ast *new);
void	ft_astadd_right(t_ast **ast, t_ast *new);
t_ast	*ft_astnew(t_list *lst_token, int len);
void	create_ast(t_ast *node);
void	test_ast(t_minishell *minishell);

# endif
