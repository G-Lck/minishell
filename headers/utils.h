/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define EXIT_SHELL 2
# define PATH_MAX 4096

typedef struct s_ast		t_ast;
typedef struct s_minishell	t_minishell;

// command_finder
char	*find_command(t_ast *node, int *status, t_minishell *minishell);

// token_utils
int		ft_lstlen(t_list *lst);
char	**tokens_to_args(t_list *token_list);

// shlvl
void	update_shlvl(t_env **env);

#endif
