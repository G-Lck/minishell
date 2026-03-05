/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance           #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALISATION_H
# define INITIALISATION_H

# include "../libft/libft.h"

typedef struct s_minishell	t_minishell;

void	init_minishell(t_minishell *minishell, char *envp[]);

#endif