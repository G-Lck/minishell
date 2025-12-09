/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:35:07 by theo              #+#    #+#             */
/*   Updated: 2025/12/09 13:43:28 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wspace(int c)
{
	if (c >= 9 && c <= 13 || c == 32)
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
