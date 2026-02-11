#ifndef MINI_H
# define MINI_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

# include "../libft/libft.h"

# include "token.h"
# include "ast.h"
# include "builtins.h"
# include "pipeline.h"


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
	int		previous_last_status;
}	t_minishell;

void	ast_descent(t_ast *node, t_minishell *data);
int	command_preparation(t_ast *node, t_minishell *minishell);
char **wildcards_parser(char *pattern, t_minishell *minishell);
char	*get_token_literal(char *token_literal, t_minishell *minishell);
char *find_command(t_ast *node, int *status, char *envp[]);
char	*ft_strcat(char *dest, char *src);
char 	*find_command(t_ast *node, int *status, char **envp);
void	exec_node(t_ast *node, t_minishell *data);
void	exec_node_no_pipeline(t_ast *node, t_minishell *data);
int		is_builtin(char **args);
void	exec_pipeline(t_ast *node, t_minishell *data);
char	**tokens_to_args(t_list *token_list);
int	tokenizer(char *cmd_line, t_minishell *minishell);
int	create_token(char *str, int type, int index, t_minishell *minishell);
int	get_token_type(char *token);
void	pop_token(int index, t_list **head);
int	fill_env(t_env **env, char *envp[]);
char	*get_env_value(char *key, t_minishell *minishell);
void	free_env2(t_env **head);
int	syntax_checker(t_minishell *minishell);
void	free_tab(char **tab);
int	need_to_glob(char *token_literal);
int	check_wspaces(char *str);
int		is_wspace(int c);
int		is_separator(char *str, int index);
int		is_operator(char *str, int index);
void	free_token_list(t_list **head);
char	*string_cleaner(char *string);
void	print_token(t_minishell *minishell);
t_token	*split_expension(char *literal, int *token_count, t_minishell *minishell);
void	exec_executable(t_ast *node, t_minishell *minishell, bool in_pipeline);
void	cleanup_minishell(t_minishell *minishell);
#endif
