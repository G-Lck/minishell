/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:07 by theo              #+#    #+#             */
/*   Updated: 2025/12/10 15:43:43 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_operators_doublons(t_minishell *minishell)
{
	t_token	*token_content;
	t_list	*token_lst;
	int		token_type;

	token_lst = minishell->tokens_list;
	while (token_lst)
	{
		token_content = token_lst->content;
		token_type = token_content->type;
		if (token_type!= STRING
			&& token_type != OPEN_BRACKET
			&& token_type != CLOSE_BRACKET)
		{
			if (!token_lst->next)
				return (0);
			token_content = token_lst->next->content;
			if (token_type == token_content->type)
					return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

int	syntax_checker(t_minishell *minishell)
{
	if (!check_operators_doublons(minishell))
	{
		ft_printf("error");
		return (0);
	}
	return (1);
}