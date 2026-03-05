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

#ifndef SIGNALS_H
# define SIGNAL_H

# include "../libft/libft.h"

typedef struct s_minishell	t_minishell;

void sigint_heredoc(int sig);
void sigint_exec(int sig);
void sigquit_exec(int sig);
void sig_handler(int sig);
void init_signals(void);

#endif