#ifndef MINI_H
# define MINI_H

# include "../libft/libft.h"
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "fcntl.h"

typedef struct s_token t_token;

typedef enum e_token_type
{
	AND = 0,
	OR = 1,
	PIPE = 2,
	OPEN_BRACKET = 3,
	CLOSE_BRACKET = 4,
	HERE_DOC = 5,
	APPEND = 6,
	REDIR_IN = 7,
	REDIR_OUT = 8,
	STRING = 9,
	TOKEN_ERROR = 10
} t_token_type;

typedef struct s_token
{
	char	*literal;
	int		type;
	int		index;
}	t_token;



typedef struct s_minishell
{
	t_list	*tokens_list;
	char	*input;
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

#endif
