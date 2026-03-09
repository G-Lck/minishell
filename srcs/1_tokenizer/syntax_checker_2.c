/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:07 by theo              #+#    #+#             */
/*   Updated: 2026/01/19 11:49:38 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string(t_minishell *minishell)
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

int	input_is_empty(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (!is_wspace(str[index]))
			return (0);
		index ++;
	}
	return (1);
}

void	check_quotes_while(char *str, int *quotes_c, int *dequotes_c)
{
	int	index;
	int	in_quotes;
	int	in_dquotes;

	index = 0;
	in_quotes = 0;
	in_dquotes = 0;
	while (str[index])
	{
		if (str[index] == '"' && in_quotes == 0)
		{
			in_dquotes = !in_dquotes;
			(*dequotes_c)++;
		}
		else if (str[index] == '\'' && in_dquotes == 0)
		{
			in_quotes = !in_quotes;
			(*quotes_c)++;
		}
		index ++;
	}
}

int	check_quotes(char *token_literal)
{
	int	quotes_counter;
	int	dquotes_counter;

	quotes_counter = 0;
	dquotes_counter = 0;
	check_quotes_while(token_literal, &quotes_counter, &dquotes_counter);
	if (quotes_counter % 2 == 1 || dquotes_counter % 2 == 1)
		return (0);
	return (1);
}
