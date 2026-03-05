/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance           #+#    #+#             */
/*   Updated: 2026/03/05 23:10:38 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALISATION_H
# define INITIALISATION_H

# include "../libft/libft.h"

typedef struct s_minishell	t_minishell;

void	safe_readline(char **input);
void	init_minishell(t_minishell *minishell, char *envp[]);
int		process_ast(t_minishell *minishell);
int		process_input(t_minishell *minishell);

#endif
