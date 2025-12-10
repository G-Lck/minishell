/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:43:07 by thbouver          #+#    #+#             */
/*   Updated: 2025/12/10 16:12:00 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Parcours la liste et libere la chaine de characetere literal du token, le
content ainsi que la node.
*/
void	free_token_list(t_list **head)
{
	t_list *tmp;
	t_token *node;

	while (*head)
	{
		tmp = *head;
		node = tmp->content;
		*head = (*head)->next;
		free (node->literal);
		free (node);
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

/*Supprime un token via son index*/
void	pop_token(int index, t_list **head)
{
	t_list	*tmp;
	t_list	*tmp1;
	t_token	*node_content;

	tmp = *head;
	if (index == 0)
	{
		tmp = (*head);
		*head = (*head)->next;
		node_content = tmp->content;
		reset_tokens_index(*head);
		return (free_token(tmp));
	}
	while (tmp->next != NULL)
	{
		node_content = tmp->next->content;
		if (node_content->index == index)
		{
			tmp1 = tmp->next;
			tmp->next = tmp->next->next;
			free_token(tmp1);
			reset_tokens_index(*head);
			return ;
		}
		tmp = tmp->next;
	}
}
