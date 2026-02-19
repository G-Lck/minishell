#ifndef CLEAN_H
# define CLEAN_H

typedef struct s_minishell t_minishell;

void	free_tab(char **tab);
void	cleanup_minishell(t_minishell *minishell);

#endif