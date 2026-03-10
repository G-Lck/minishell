/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance           #+#    #+#             */
/*   Updated: 2026/03/04 17:01:00 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_readline(char **input)
{
	int	saved_stdout;

	if (isatty(STDIN_FILENO))
		*input = readline("\e[0;36mMinishell> \e[0;33m");
	else
	{
		saved_stdout = dup(STDOUT_FILENO);
		dup2(open("/dev/null", O_WRONLY), STDOUT_FILENO);
		*input = readline(NULL);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	process_ast(t_minishell *minishell)
{
	if (!convert_all_heredoc(minishell))
		return (0);
	minishell->ast = ft_astnew(minishell->tokens_list,
			ft_lstsize(minishell->tokens_list));
	create_ast(minishell->ast);
	rl_reset_terminal(NULL);
	ast_descent(minishell->ast, minishell);
	free_ast(minishell->ast);
	return (1);
}

int	process_input(t_minishell *minishell)
{
	if (minishell->input == NULL)
		return (0);
	if (input_is_empty(minishell->input))
		return (free(minishell->input), 1);
	if (ft_strlen(minishell->input) == 0)
		return (free(minishell->input), 1);
	if (isatty(STDIN_FILENO))
		add_history(minishell->input);
	tokenizer(minishell->input, minishell);
	if (syntax_checker(minishell) && !process_ast(minishell))
	{
		minishell->previous_status = minishell->status;
		free_token_list(&minishell->tokens_list);
		return (free(minishell->input), 1);
	}
	minishell->previous_status = minishell->status;
	free_token_list(&minishell->tokens_list);
	free(minishell->input);
	return (1);
}
