/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_heredoc_line(char *eof)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("> ");
	else
		line = readline(NULL);
	if (!line && !g_sig)
	{
		ft_putstr_fd("minishell: warning: ", 2);
		ft_putstr_fd("here-document delimited by EOF (wanted '", 2);
		ft_putstr_fd(eof, 2);
		ft_putstr_fd("')\n", 2);
	}
	return (line);
}

static int	heredoc_event_hook(void)
{
	if (g_sig)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

static char	*append_heredoc_line(char *content, char *line)
{
	char	*tmp;

	tmp = content;
	content = ft_strjoin(content, line);
	free(tmp);
	tmp = content;
	content = ft_strjoin(content, "\n");
	free(tmp);
	return (content);
}

static int	process_heredoc_line(char **content, char *eof)
{
	char	*line;

	line = read_heredoc_line(eof);
	if (g_sig)
	{
		free(line);
		free(*content);
		*content = NULL;
		return (0);
	}
	if (!line || !ft_strcmp(line, eof))
	{
		free(line);
		return (0);
	}
	*content = append_heredoc_line(*content, line);
	free(line);
	return (1);
}

char	*read_heredoc(char *eof)
{
	char	*content;
	int		saved_sig;

	init_heredoc_signals();
	rl_event_hook = heredoc_event_hook;
	content = ft_strdup("");
	while (process_heredoc_line(&content, eof))
		;
	rl_event_hook = NULL;
	saved_sig = g_sig;
	init_signals();
	g_sig = saved_sig;
	return (content);
}
