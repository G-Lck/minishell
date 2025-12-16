#ifndef TOKEN_H
# define TOKEN_H

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

#endif