/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:07 by theo              #+#    #+#             */
/*   Updated: 2025/12/10 17:57:49 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check si le token suivant un operator est bien un token de type string
ou une parenthese ouverte
Renvoie une erreur sinon*/
static int	check_after_operator(t_minishell *minishell)
{
	t_token			*token_content;
	t_list			*token_lst;
	t_token_type	token_type;

	token_lst = minishell->tokens_list;
	while (token_lst)
	{
		token_content = token_lst->content;
		token_type = token_content->type;
		if (token_type != STRING
			&& token_type != OPEN_BRACKET
			&& token_type != CLOSE_BRACKET)
		{
			if (!token_lst->next)
				return (0);
			token_content = token_lst->next->content;
			if (token_content->type != STRING
				&& token_content->type != OPEN_BRACKET)
				return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

/*check le premier token de chaque debut de subshell, renvoie une erreur si
ce n'est pas un token de type string, ou parenthese ou dans le cas d'un
subshell, si le token n'est egalement pas une parenthèse fermée*/
static int	check_first_token(t_minishell *minishell)
{
	t_list		*token_lst;
	t_token		*token_content;	

	token_lst = minishell->tokens_list;
	while (token_lst)
	{
		token_content = token_lst->content;
		if (token_content->index == 0)
		{
			if (token_content->type != STRING
				&& token_content->type != OPEN_BRACKET
				&& token_content->type != CLOSE_BRACKET)
				return (0);
		}
		if (token_content->type == OPEN_BRACKET)
		{
			if (token_lst->next)
			{
				token_content = token_lst->next->content;
				if (token_content->type != STRING
					&& token_content->type != OPEN_BRACKET
					&& token_content->type != CLOSE_BRACKET)
					return (0);
			}
		}
		token_lst = token_lst->next;
	}
	return (1);
}


/*Point d'entrée du check syntaxique de la liste de tokens*/
int	syntax_checker(t_minishell *minishell)
{
	if (!check_after_operator(minishell) || !check_first_token(minishell))
	{
		ft_printf("error");
		return (0);
	}
	return (1);
}