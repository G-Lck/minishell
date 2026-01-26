/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:35:07 by theo              #+#    #+#             */
/*   Updated: 2026/01/26 13:32:20 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

int	is_separator(char *str, int index)
{
	if (is_wspace(str[index]))
		return (1);
	else
	{
		if (str[index] == '&' && str[index + 1] == '&')
			return (1);
		if (str[index] == '|' && str[index + 1] == '|')
			return (1);
		if (str[index] == '>' && str[index + 1] == '>')
			return (1);
		if (str[index] == '<' && str[index + 1] == '<')
			return (1);
		if (str[index] == '|' || str[index] == '(' || str[index] == ')'
			|| str[index] == '>'
			|| str[index] == '<')
		{
			return (1);
		}
	}
	return (0);
}

int	is_operator(char *str, int index)
{
	if (str[index] == '&' && str[index + 1] == '&')
		return (1);
	if (str[index] == '|' && str[index + 1] == '|')
		return (1);
	if (str[index] == '>' && str[index + 1] == '>')
		return (1);
	if (str[index] == '<' && str[index + 1] == '<')
		return (1);
	if (str[index] == '|' || str[index] == '(' || str[index] == ')'
		|| str[index] == '>'
		|| str[index] == '<')
	{
		return (1);
	}
	return (0);
}

/*
Identifie et retourne le type de token
*/
int	get_token_type(char *token)
{
	if (ft_strlen(token) == 2)
	{
		if (token[1] == '|')
			return (OR);
		else if (token[1] == '&')
			return (AND);
		else if (token[1] == '<')
			return (HERE_DOC);
		else
			return (APPEND);
	}
	else
	{
		if (token[0] == '|')
			return (PIPE);
		else if (token[0] == '(')
			return (OPEN_BRACKET);
		else if (token[0] == ')')
			return (CLOSE_BRACKET);
		else if (token[0] == '<')
			return (REDIR_IN);
		else
			return (REDIR_OUT);
	}
	return (TOKEN_ERROR);
}

/*Parcours la liste de token et affiche leurs valeurs*/
void	print_token(t_minishell *minishell)
{
	t_list	*tmp;
	t_token	*node;

	tmp = minishell->tokens_list;
	while (tmp)
	{
		node = tmp->content;
		ft_printf("[%s] -> ", node->literal);
		tmp = tmp->next;
	}
}
