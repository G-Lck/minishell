/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:43:07 by thbouver          #+#    #+#             */
/*   Updated: 2026/02/07 12:18:26 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Parcours la liste et libere la chaine de characetere literal du token, le
content ainsi que la node.
*/
void	free_token_list(t_list **head)
{
	t_list	*tmp;
	t_token	*token;

	while (*head)
	{
		tmp = *head;
		token = tmp->content;
		*head = (*head)->next;
		if (token && token->literal)
			free (token->literal);
		free (token);
		free (tmp);
	}
	*head = NULL;
}

/*Creer un nouveau token et l'ajoute a la liste de tokens.*/
int	create_token(char *str, int type, int index, t_minishell *minishell)
{
	t_list	*new_node;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->literal = ft_strdup(str);
	if (!new_token->literal)
		return (0);
	new_token->type = type;
	new_node = ft_lstnew(new_token);
	if (!new_node)
		return (0);
	new_token->index = index;
	ft_lstadd_back(&minishell->tokens_list, new_node);
	return (1);
}

/*Recalcule l'index de chaque token*/
void	reset_tokens_index(t_list *head)
{
	t_token	*node_content;
	int		index;

	index = 0;
	while (head)
	{
		node_content = head->content;
		node_content->index = index;
		head = head->next;
		index ++;
	}
}

/*Libere la memoire d'un token precis*/
void	free_token(t_list *node)
{
	t_token	*token_node;

	token_node = node->content;
	free (token_node->literal);
	free (token_node);
	free (node);
}
