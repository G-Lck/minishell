# ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

#define EXIT_SHELL 2

typedef struct s_minishell t_minishell;
typedef struct s_env t_env;

int		ft_exit(t_list *args, t_minishell *minishell);

int		ft_echo(char **args, t_env *env);
char	*expand_variables(char *str, t_env *env);


# endif
