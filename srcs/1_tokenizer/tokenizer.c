/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:08:35 by theo              #+#    #+#             */
/*   Updated: 2026/01/29 18:14:48 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Fonction inutile pour le moment.
Permet de supprimer les doubles quotes et singles quotes de delimation tout
en preservant ceux a afficher
*/

/*
String_Tokenizer s'occupe de creer les tokens sur les chaines de characteres.
Une chaine de characetre est delimitee par un operateur logique, un whitespace
ou une parenthese.
La fonction n'enleve pas les doubles quotes et les singles quotes delimitant
les chaines.
Elle ajoute une nouvelle node a la liste t_list *tokens_list et lui donne
t_token *node en contenu.
*/
static int	string_tokenizer(char *cmd, int *i, t_minishell *mini, int c_index)
{
	char	*tmp;
	int		in_quotes;
	int		in_dquotes;
	int		current;

	current = *i;
	in_quotes = 0;
	in_dquotes = 0;
	while (cmd[*i])
	{
		if (cmd[*i] == '"' || cmd[*i] == 39)
		{
			if (cmd[*i] == '"' && in_quotes == 0)
				in_dquotes = !in_dquotes;
			if (cmd[*i] == 39 && in_dquotes == 0)
				in_quotes = !in_quotes;
		}
		if (is_separator(cmd, *i) && in_quotes == 0 && in_dquotes == 0)
			break ;
		*i += 1;
	}
	tmp = ft_substr(cmd, current, (*i - current));
	if (!tmp)
		return (0);
	if (!create_token(tmp, STRING, c_index, mini))
		return (free(tmp), 0);
	return (free(tmp), 1);
}

/*
Operator_Tokenizer s'occupe de creer les tokens sur les operateurs logique ainsi
que sur les parentheses.
Elle ajoute une nouvelle node a la liste t_list *tokens_list et lui donne
t_token *node en contenu.
*/
static int	operator_tokenizer(char *cmd, int *i, t_minishell *mini, int tindex)
{
	char	*tmp;
	int		ptr_index;

	ptr_index = 0;
	tmp = ft_calloc(sizeof(char), 3);
	if (!tmp)
		return (0);
	tmp[ptr_index ++] = cmd[*i];
	*i += 1;
	if (cmd[*i] && ((cmd[*i] == '&' && cmd[*i - 1] == '&')
			|| (cmd[*i] == '|' && cmd[*i - 1] == '|')
			|| (cmd[*i] == '>' && cmd[*i - 1] == '>')
			|| (cmd[*i] == '<' && cmd[*i - 1] == '<')))
	{
		tmp[ptr_index ++] = cmd[*i];
		*i += 1;
	}
	if (!create_token(tmp, get_token_type(tmp), tindex, mini))
		return (free(tmp), 0);
	return (free(tmp), 1);
}

/*
Fonction d'entree du tokenizer
La fonction lit l'input du shell et creer des tokens en fonction des operateurs,
des whites space ainsi que des chaines de characteres.
L'index est directement modifier par les fonctions qui creer les tokens.
Les fonctions renvoies 0 en cas d'erreurs d'allocations.
*/
int	tokenizer(char *cmd_line, t_minishell *mini)
{
	int	current_t_index;
	int	index;

	current_t_index = 0;
	index = 0;
	while (cmd_line[index])
	{
		if (cmd_line[index] == '"' || cmd_line[index] == 39
			|| !is_separator(cmd_line, index))
		{
			if (!string_tokenizer(cmd_line, &index, mini, current_t_index ++))
				return (free_token_list(&mini->tokens_list), 0);
		}
		else if (is_operator(cmd_line, index))
		{
			if (!operator_tokenizer(cmd_line, &index, mini, current_t_index ++))
				return (free_token_list(&mini->tokens_list), 0);
		}
		else
			index ++;
	}
	return (1);
}
