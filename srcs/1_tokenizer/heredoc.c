#include "minishell.h"

char	*read_heredoc_line(char *eof)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("> ");
	else
		line = readline(NULL);
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by EOF (wanted '", 2);
		ft_putstr_fd(eof, 2);
		ft_putstr_fd("')\n", 2);
	}
	return (line);
}

void here_doc_handler(int sig)
{
	(void)sig;
	g_sig = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
}

void init_heredoc_signals(void)
{
	struct sigaction sig;
	sig.sa_handler = here_doc_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
}

char	*read_heredoc(char *eof)
{
	char	*line;
	char	*content;
	char	*tmp;

	init_heredoc_signals();
	content = ft_strdup("");
	while (1)
	{
		line = read_heredoc_line(eof);
		if (g_sig)
		{
			free(line);
			free(content);
			content = NULL;
			break;
		}
		if (!line || !ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		tmp = content;
		content = ft_strjoin(content, line);
		free(tmp);
		tmp = content;
		content = ft_strjoin(content, "\n");
		free(tmp);
		free(line);
	}
	g_sig = 0;
	init_signals();
	return (content);
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
