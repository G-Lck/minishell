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