# ifndef AST_H
# define AST_H

# ifndef NODE_TYPE
# define OPERATION 0
# define VALUE 1
# endif

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_ast
{
	int type;
	char *raw;
	struct s_ast *next_left;
	struct s_ast *next_right;
} t_ast;


t_ast	*ft_astnew(char *content, int type);

# endif