/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:43:07 by thbouver          #+#    #+#             */
/*   Updated: 2026/02/07 12:18:26 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lst_go_to(t_list *lst, int position)
{
	int	i;

	i = 0;
	while (i < position && lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

int	switch_p(int type, int p)
{
	if (type == OPEN_BRACKET)
		p++;
	if (type == CLOSE_BRACKET)
		p--;
	return (p);
}

void	remove_parenthesis(t_ast *node, int p)
{
	int		i;
	t_list	*lst_token;
	t_token	*token;

	lst_token = node->lst_token;
	token = lst_token->content;
	i = 0;
	while (i++ < node ->lst_len - 1)
	{
		p = switch_p(token->type, p);
		if (p == 0)
			return ;
		lst_token = lst_token->next;
		token = lst_token->content;
	}
	if (token->type != CLOSE_BRACKET)
		return ;
	node->is_subshell = true;
	lst_token = node->lst_token;
	lst_token = lst_token->next;
	node->lst_token = lst_token;
	node->lst_len -= 2;
	remove_parenthesis(node, 0);
}

int	is_op(t_token_type t)
{
	if (t == AND || t == OR)
		return (1);
	return (0);
}

int	is_pipe(t_token_type t)
{
	if (t == PIPE)
		return (1);
	return (0);
}
