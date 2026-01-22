#ifndef MINI_H
# define MINI_H

# include "../libft/libft.h"
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "errno.h"
# include "fcntl.h"
# include "stdbool.h"
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "token.h"
# include "ast.h"
# include "builtins.h"

typedef struct s_token t_token;
typedef struct s_ast t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}   t_env;

typedef enum e_cmd_status
{
	PERMISSION_DENIED = 0,
	IS_DIRECTORY = -1,
	COMMAND_NOT_FOUND = -2,
	OK = 1
} t_cmd_status;

typedef struct s_minishell
{
	t_env	*env;
	t_list	*tokens_list;
	t_ast	*ast;
	char	*input;
	char	**envp;
	char	*current_dir;
	int		exit_code;
	int		last_status;
}	t_minishell;

void	ast_descent(t_ast *node, t_minishell *data);
int	node_preparation(t_ast *node, t_minishell *minishell);
char 	*find_command(t_ast *node, int *status, char **envp);
void	exec_node(t_ast *node, t_minishell *data);
void	exec_pipeline(t_ast *node, t_minishell *data);

//Parser/Tokenizer
int	tokenizer(char *cmd_line, t_minishell *minishell);
int	create_token(char *str, int type, int index, t_minishell *minishell);
int	get_token_type(char *token);
void	pop_token(int index, t_list **head);
int	feel_env(t_env **env, char *envp[]);
char	*get_env_value(char *key, t_env *env);
int	syntax_checker(t_minishell *minishell);
void	free_tab(char **tab);

//Utils
int		is_wspace(int c);
int		is_separator(char *str, int index);
int		is_operator(char *str, int index);
void	free_token_list(t_list **head);
void	print_token(t_minishell *minishell);


#endif
