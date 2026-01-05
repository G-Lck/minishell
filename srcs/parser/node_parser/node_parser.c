/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:35:07 by theo              #+#    #+#             */
/*   Updated: 2026/01/05 15:00:29 by thbouver         ###   ########.fr       */
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
	ft_printf("%d target : %s\n", type, target);
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
		if (token->type == REDIR_IN || token->type == REDIR_OUT)
		{
			if (node->lst_token->next == NULL)
				break ;
			tmp = node->lst_token->next->content;
			create_redir_node(tmp->literal, token->type, node);
			node->lst_token = node->lst_token->next;
			index ++;
		}
		node->lst_token = node->lst_token->next;
		index ++;
	}
	ft_printf("\n");
}