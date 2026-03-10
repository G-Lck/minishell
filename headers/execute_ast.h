/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/03/10 23:30:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_AST_H
# define EXECUTE_AST_H

# include "../libft/libft.h"

typedef struct s_ast		t_ast;
typedef struct s_minishell	t_minishell;

void	exec_in_pipeline(t_ast *node, t_minishell *minishell);
void	exec_no_pipeline(t_ast *node, t_minishell *minishell);
void	ast_descent(t_ast *node, t_minishell *minishell);

#endif
