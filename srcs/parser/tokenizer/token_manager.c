/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:43:07 by thbouver          #+#    #+#             */
/*   Updated: 2025/12/09 15:05:32 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_minishell *minishell)
{
	t_list	*tmp;
	t_token	*node;

	tmp = minishell->tokens_list;
	while (tmp)
	{
		node = tmp->content;
		ft_printf("[%s (%d)] -> ", node->token, node->type);
		tmp = tmp->next;
	}
}

void	free_token_list(t_list **head)
{
	t_list *tmp;
	t_token *node;

	while (*head)
	{
		tmp = *head;
		node = tmp->content;
		*head = (*head)->next;
		free (node->token);
		free (node);
		free (tmp);
	}
	*head = NULL;
}

int	create_token(char *str, int type, t_minishell *minishell)
{
	t_list	*new_node;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->token = ft_strdup(str);
	if (!new_token->token)
		return (0);
	new_token->type = type;
	new_node = ft_lstnew(new_token);
	if (!new_node)
		return (0);
	ft_lstadd_back(&minishell->tokens_list, new_node);
	return (1);
}