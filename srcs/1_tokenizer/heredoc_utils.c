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
	g_sig = 130;
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

static int	is_quoted_eof(char *eof)
{
	if (eof[0] == '\'' || eof[0] == '"')
		return (1);
	return (0);
}

static int	process_heredoc_token(t_token *nt, t_minishell *m, int quoted)
{
	char	*content;
	char	*clean_eof;

	clean_eof = ft_strdup(nt->literal);
	clean_eof = string_cleaner(clean_eof);
	content = read_heredoc(clean_eof);
	free(clean_eof);
	if (!content)
	{
		m->status = g_sig;
		g_sig = 0;
		return (0);
	}
	free(nt->literal);
	if (!quoted)
		nt->literal = expand_variables(content, m);
	else
		nt->literal = ft_strdup(content);
	free(content);
	return (1);
}

int	convert_all_heredoc(t_minishell *minishell)
{
	t_list	*current;
	t_token	*token;
	t_token	*next_token;

	current = minishell->tokens_list;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == HERE_DOC && current->next)
		{
			next_token = (t_token *)current->next->content;
			if (!process_heredoc_token(next_token, minishell,
					is_quoted_eof(next_token->literal)))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
