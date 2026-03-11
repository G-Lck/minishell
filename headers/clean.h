/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

typedef struct s_minishell	t_minishell;

void	free_tab(char **tab);
void	cleanup_minishell(t_minishell *minishell);
void	free_minishell(t_minishell *minishell);
void	clean_exit(t_minishell *minishell, int exit_code);
void	clean_exit_pipeline(t_minishell *minishell, t_pipeline *p, int code);

#endif
