/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_preparation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:35:07 by theo              #+#    #+#             */
/*   Updated: 2026/01/14 14:12:44 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_redir_node(char *target, t_token_type type, t_ast *node)
{
	t_list	*new_node;
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);
	new_redir->redir_type = type;
	new_redir->target = ft_strdup(target);
	if (!new_redir->target)
		return(0);
	new_node = ft_lstnew(new_redir);
	if (!new_node)
		return (free(new_redir->target), free(new_redir), 0);
	ft_lstadd_back(&node->redirs, new_node);
	//ft_printf("redir : %d -> %s\n", new_redir->redir_type, new_redir->target);
	return (1);
}

int	create_command_node(t_token *token, t_ast *node)
{
	t_list	*new_node;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->literal = ft_strdup(token->literal);
	if (!new_token->literal)
		return (free(new_token),0);
	new_token->type = token->type;
	new_node = ft_lstnew(new_token);
	if (!new_node)
		return (free(new_token->literal), free(new_token), 0);
	ft_lstadd_back(&node->exec_token, new_node);
	//ft_printf("token basic : %s\n", token->literal);
	return (1);
}

int	node_preparation(t_ast *node)
{
	int	index = 0;
	t_token *token;
	t_token *tmp;

	while (index < node->lst_len)
	{
		token = node->lst_token->content;
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == HERE_DOC || token->type == APPEND)
		{
			tmp = node->lst_token->next->content;
			create_redir_node(tmp->literal, token->type, node);
			node->lst_token = node->lst_token->next;
			index ++;
		}
		else
			create_command_node(token, node);
		node->lst_token = node->lst_token->next;
		index ++;
	}
//	ft_printf("\n");
}
