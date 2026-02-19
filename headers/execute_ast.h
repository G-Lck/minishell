#ifndef EXECUTE_AST_H
# define EXECUTE_AST_H

# include "../libft/libft.h"

typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;

void	exec_executable(t_ast *node, t_minishell *minishell, bool in_pipeline);
int	ft_lstlen(t_list *lst);
char **tokens_to_args(t_list *token_list);
void	ast_descent(t_ast *node, t_minishell *minishell);

#endif