/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:07 by theo              #+#    #+#             */
/*   Updated: 2026/01/06 16:42:58 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check si le token suivant un operator est bien un token de type string
ou une parenthese ouverte
Renvoie une erreur sinon*/
static int	check_after_operator(t_minishell *minishell)
{
	t_token			*token_content;
	t_list			*token_lst;
	t_token_type	token_type;

	token_lst = minishell->tokens_list;
	while (token_lst)
	{
		token_content = token_lst->content;
		token_type = token_content->type;
		if (token_type != STRING
			&& token_type != OPEN_BRACKET
			&& token_type != CLOSE_BRACKET)
		{
			if (!token_lst->next)
				return (0);
			token_content = token_lst->next->content;
			if (token_content->type != STRING
				&& token_content->type != OPEN_BRACKET)
				return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

/*check le premier token de chaque debut de subshell, renvoie une erreur si
ce n'est pas un token de type string, ou parenthese ou dans le cas d'un
subshell, si le token n'est egalement pas une parenthèse fermée*/
static int	check_first_token(t_minishell *minishell)
{
	t_list		*token_lst;
	t_token		*token_content;	

	token_lst = minishell->tokens_list;
	while (token_lst)
	{
		token_content = token_lst->content;
		if (token_content->index == 0)
		{
			if (token_content->type != STRING
				&& token_content->type != OPEN_BRACKET
				&& token_content->type != CLOSE_BRACKET)
				return (0);
		}
		if (token_content->type == OPEN_BRACKET)
		{
			if (token_lst->next)
			{
				token_content = token_lst->next->content;
				if (token_content->type != STRING
					&& token_content->type != OPEN_BRACKET
					&& token_content->type != CLOSE_BRACKET)
					return (0);
			}
		}
		token_lst = token_lst->next;
	}
	return (1);
}

/*check si les parentheses sont bien ouverte et fermee*/
static int	bracket_checker(t_minishell *minishell)
{
	t_list	*token_lst;
	t_token	*token_content;
	int		bracket_counter;

	bracket_counter = 0;
	token_lst = minishell->tokens_list;
	while (token_lst)
	{
		token_content = token_lst->content;
		if (token_content->type == OPEN_BRACKET)
			bracket_counter ++;
		else if (token_content->type == CLOSE_BRACKET)
			bracket_counter --;
		if (bracket_counter < 0)
			return (0);
		token_lst = token_lst->next;
	}
	if (bracket_counter != 0)
		return (0);
	return (1);
}

/*check si les quotes et doubles quotes sont fermee*/
static int	check_quotes(char *token_literal)
{
	int	index;
	int	in_quotes;
	int	in_dquotes;
	int	quotes_counter;
	int	dquotes_counter;

	index = 0;
	in_quotes = 0;
	in_dquotes = 0;
	quotes_counter = 0;
	dquotes_counter = 0;
	while (token_literal[index])
	{
		if(token_literal[index] == '"' && in_quotes == 0)
		{
			in_dquotes = !in_dquotes;
			dquotes_counter ++;
		}
		else if (token_literal[index] == '\'' && in_dquotes == 0)
		{
			in_quotes = !in_quotes;
			quotes_counter ++;
		}
		index ++;
	}
	if (quotes_counter % 2 == 1 || dquotes_counter % 2 == 1)
		return (0);
	return (1);
}

static int	check_string(t_minishell *minishell)
{
	t_list	*token_lst;
	t_token	*token_content;

	token_lst = minishell->tokens_list;
	while (token_lst)
	{
		token_content = token_lst->content;
		if (token_content->type == STRING)
		{
			if (!check_quotes(token_content->literal))
				return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

/*Point d'entrée du check syntaxique de la liste de tokens*/
int	syntax_checker(t_minishell *minishell)
{
	if (!check_after_operator(minishell) || !check_first_token(minishell))
	{
		ft_printf("operators must be followed by a command\n");
		return (0);
	}
	if (!check_string(minishell))
	{
		ft_printf("quotes must be closed\n");
		return (0);
	}
	if (!bracket_checker(minishell))
	{
		ft_printf("parentheses must be closed\n");
		return (0);
	}
	return (1);
}