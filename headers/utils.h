#ifndef UTILS_H
# define UTILS_H

#define EXIT_SHELL 2
#define PATH_MAX 4096

typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;


// command_finder
char *find_command(t_ast *node, int *status, t_minishell *minishell);

#endif