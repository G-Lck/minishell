/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_handler(int sig)
{
	(void)sig;
	g_sig = 1;
}

void	init_heredoc_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = here_doc_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	convert_all_heredoc(t_minishell *minishell)
{
	t_list	*current;
	t_token	*token;
	t_token	*next_token;
	char	*content;

	current = minishell->tokens_list;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == HERE_DOC && current->next)
		{
			next_token = (t_token *)current->next->content;
			content = read_heredoc(next_token->literal);
			if (!content)
				return (0);
			free(next_token->literal);
			next_token->literal = content;
		}
		current = current->next;
	}
	return (1);
}
