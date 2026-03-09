/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:07 by theo              #+#    #+#             */
/*   Updated: 2026/01/19 11:49:38 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_redir_node(char *target, t_token_type type)
{
	t_list	*new_node;
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->redir_type = type;
	new_redir->target = ft_strdup(target);
	if (!new_redir->target)
		return (NULL);
	new_node = ft_lstnew(new_redir);
	return (new_node);
}

t_list	*new_exec_node(char *token_literal, t_token_type type)
{
	t_list	*new_node;
	t_token	*new_exec_token;

	new_exec_token = malloc(sizeof(t_token));
	if (!new_exec_token)
		return (NULL);
	new_exec_token->type = type;
	new_exec_token->literal = ft_strdup(token_literal);
	if (!new_exec_token->literal)
		return (NULL);
	new_node = ft_lstnew(new_exec_token);
	return (new_node);
}

static void	string_cleaner_while(char *str, char *cleaned_string)
{
	int	index;
	int	index_2;
	int	in_quote;
	int	in_dquote;

	index = 0;
	in_quote = 0;
	in_dquote = 0;
	index_2 = 0;
	while (str[index])
	{
		if (str[index] == '"' && in_quote == 0)
		{
			in_dquote = !in_dquote;
			index ++;
		}
		else if (str[index] == '\'' && in_dquote == 0)
		{
			in_quote = !in_quote;
			index ++;
		}
		else
			cleaned_string[index_2 ++] = str[index ++];
	}
}

char	*string_cleaner(char *string)
{
	char	*cleaned_string;

	cleaned_string = ft_calloc(sizeof(char), ft_strlen(string) + 1);
	if (!cleaned_string)
		return (0);
	string_cleaner_while(string, cleaned_string);
	free(string);
	return (cleaned_string);
}

int	check_wspaces(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
			return (1);
		index ++;
	}
	return (0);
}
