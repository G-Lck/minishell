#ifndef EXPANSION_AND_WILDCARDS_H
# define EXPANSION_AND_WILDCARDS_H

# include "../libft/libft.h"

typedef struct s_minishell t_minishell;
typedef struct s_ast t_ast;
typedef struct s_token t_token;
typedef enum e_token_type t_token_type;

// command_preparation
t_list	*new_redir_node(char *target, t_token_type type);
t_list	*new_exec_node(char *token_literal, t_token_type type);
int	create_redir_node(char *target, t_token_type type, t_ast *node, t_minishell *minishell);
int	create_command_node(t_token *token, t_ast *node, t_minishell *minishell);
int	command_preparation(t_ast *node, t_minishell *minishell);

// expand_variables
char	*get_env_value(char *key, t_minishell *minishell);
char	*expand_variables(char *str, t_minishell *minishell);

// expansion_utils
char	*string_cleaner(char *string);
int	check_wspaces(char *str);

// expansion
int	create_token_literal(t_token *token_tab, char *str, int *index);
void	fill_token_tab(t_token *token_tab, char *expanded_token, int token_count);
int	token_counter(char *expanded_token);
t_token	*split_expension(char *literal, int *token_count, t_minishell *minishell);

// variables_parser
char	*get_var_name(char *str);

//wildcard_parser
int	is_only_wildcards(char *pat);
int	pattern_checker(char *ref, char *pat, int n, int m);
int	get_tab_size(char *pattern, t_minishell *minishell);
int	need_to_glob(char *token_literal);
char **wildcards_parser(char *pattern, t_minishell *minishell);

#endif