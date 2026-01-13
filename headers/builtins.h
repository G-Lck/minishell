# ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

#define EXIT_SHELL 2
#define PATH_MAX 4096

typedef struct s_minishell t_minishell;
typedef struct s_env t_env;

int		ft_exit(t_list *args, t_minishell *minishell);

int		ft_echo(char **args, t_env *env);
char	*expand_variables(char *str, t_env *env);
char	*get_var_name(char *str);
int		ft_env(t_env *env);
int		ft_pwd(void);
int		ft_export(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);
int		ft_cd(char **args, t_env **env);

// env_helpers.c
void	add_env_var(t_env **head, char *key, char *value);
void	set_env_var(t_env **env, char *key, char *value);
t_env	*create_env_var(char *key, char *value);
t_env	*find_env_var(t_env *env, char *key);
void	free_env(t_env *env);

// export_helpers.c
int		count_env_vars(t_env *env);
char	**create_sorted_array(t_env *env, int count);
void	bubble_sort_array(char **sorted, int count);
void	print_and_free_array(char **sorted);

# endif
