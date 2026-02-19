/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"

typedef struct s_minishell	t_minishell;

typedef enum e_token_type
{
	AND = 0,
	OR = 1,
	PIPE = 2,
	OPEN_BRACKET = 3,
	CLOSE_BRACKET = 4,
	HERE_DOC = 5,
	APPEND = 6,
	REDIR_IN = 7,
	REDIR_OUT = 8,
	STRING = 9,
	TOKEN_ERROR = 10
}	t_token_type;

typedef struct s_token
{
	char	*literal;
	int		type;
	int		index;
}	t_token;

int		syntax_checker(t_minishell *minishell);
void	free_token_list(t_list **head);
int		create_token(char *str, int type, int index, t_minishell *minishell);
void	reset_tokens_index(t_list *head);
void	free_token(t_list *node);
void	pop_token(int index, t_list **head);
int		is_wspace(int c);
int		is_separator(char *str, int index);
int		is_operator(char *str, int index);
int		get_token_type(char *token);
void	print_token(t_minishell *minishell);
int		tokenizer(char *cmd_line, t_minishell *minishell);

#endif
