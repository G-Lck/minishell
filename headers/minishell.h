#ifndef MINI_H
# define MINI_H

# include "../libft/libft.h"
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "fcntl.h"
# include "stdbool.h"
# include <readline/readline.h>
# include "token.h"
# include "ast.h"

typedef struct s_token t_token;
typedef struct s_ast t_ast;

typedef struct s_minishell
{
	t_list	*tokens_list;
	t_ast	*ast;
	char	*input;
	int		exit_code;
	int		last_status;
}	t_minishell;

//Parser/Tokenizer
int	tokenizer(char *cmd_line, t_minishell *minishell);
int	create_token(char *str, int type, int index, t_minishell *minishell);
int	get_token_type(char *token);
void	pop_token(int index, t_list **head);
int	syntax_checker(t_minishell *minishell);

//Utils
int	is_wspace(int c);
int	is_separator(char *str, int index);
int	is_operator(char *str, int index);
void	free_token_list(t_list **head);
void	print_token(t_minishell *minishell);

//exec_ast
int	exec_ast(t_ast *node);

#endif
