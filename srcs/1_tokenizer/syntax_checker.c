/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:07 by theo              #+#    #+#             */
/*   Updated: 2026/03/05 23:22:59 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check si le token suivant un operator est bien un token de type string
ou une parenthese ouverte
Renvoie une erreur sinon*/
static int	check_between_parenthesis(t_minishell *minishell)
{
	t_token			*token_content;
	t_list			*token_lst;
	t_token_type	token_type;

	token_lst = minishell->tokens_list;
	while (token_lst)
	{
		token_content = token_lst->content;
		token_type = token_content->type;
		if (token_type == OPEN_BRACKET)
		{
			if (!token_lst->next)
				return (0);
			token_content = token_lst->next->content;
			if (token_content->type == CLOSE_BRACKET)
				return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

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
			if (token_content->type == CLOSE_BRACKET
				|| token_content->type == AND || token_content->type == OR)
				return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

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
			if (token_content->type == AND || token_content->type == OR)
				return (0);
		}
		if (token_content->type == OPEN_BRACKET && token_lst->next)
		{
			token_content = token_lst->next->content;
			if (token_content->type != STRING
				&& token_content->type != OPEN_BRACKET
				&& token_content->type != CLOSE_BRACKET)
				return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

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

int	syntax_checker(t_minishell *minishell)
{
	if (!check_after_operator(minishell) || !check_first_token(minishell)
		|| !check_between_parenthesis(minishell))
	{
		ft_printf("operators must be followed by a command\n");
		minishell->status = 2;
		return (0);
	}
	if (!check_string(minishell))
	{
		ft_printf("quotes must be closed\n");
		minishell->status = 2;
		return (0);
	}
	if (!bracket_checker(minishell))
	{
		ft_printf("parentheses must be closed\n");
		minishell->status = 2;
		return (0);
	}
	return (1);
}
