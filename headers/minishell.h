/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 199309L

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>

# include "../libft/libft.h"

# include "initialisation.h"
# include "tokenizer.h"
# include "create_ast.h"
# include "expansion_and_wildcards.h"
# include "execute_ast.h"
# include "execute_cmd.h"
# include "execute_pipeline.h"
# include "clean.h"
# include "signals.h"
# include "utils.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_cmd_status
{
	PERMISSION_DENIED = 0,
	IS_DIRECTORY = -1,
	COMMAND_NOT_FOUND = -2,
	OK = 1
}	t_cmd_status;

typedef struct s_minishell
{
	t_env	*env;
	t_list	*tokens_list;
	t_ast	*ast;
	char	*input;
	char	**envp;
	char	*current_dir;
	int		exit_code;
	int		status;
	int		previous_status;
}	t_minishell;

extern volatile sig_atomic_t	g_sig;

void	sig_handler(int sig);
void	sigint_exec(int sig);
void	sigquit_exec(int sig);
void	sigint_heredoc(int sig);
void	init_signals(void);

#endif
