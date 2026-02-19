/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2026/02/19 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstlen(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**tokens_to_args(t_list *token_list)
{
	t_list	*current;
	t_token	*token;
	char	**args;
	int		i;

	if (!token_list)
		return (NULL);
	args = malloc(sizeof(char *) * (ft_lstlen(token_list) + 1));
	if (!args)
		return (NULL);
	current = token_list;
	i = 0;
	while (current)
	{
		token = (t_token *)current->content;
		if (token && token->literal)
			args[i] = ft_strdup(token->literal);
		else
			args[i] = ft_strdup("");
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
