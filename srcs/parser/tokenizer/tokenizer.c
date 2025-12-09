/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:08:35 by theo              #+#    #+#             */
/*   Updated: 2025/12/09 13:19:39 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
Inutile
*/
static int	string_cleaner(char *string, t_minishell *minishell)
{
	char	*string_token;
	int		in_quotes;
	int		in_dquotes;
	int		index;
	int		ptr_index;

	ptr_index = 0;
	index = 0;
	in_dquotes = 0;
	in_quotes = 0;
	string_token = ft_calloc(sizeof(char), ft_strlen(string + 1));
	if (!string_token)
		return (-1);
	while (string[index])
	{
		if (string[index] == '"' && in_quotes == 0)
			in_dquotes = !in_dquotes;
		else if (string[index] == 39 && in_dquotes == 0)
			in_quotes = !in_quotes;
		if ((string[index] == '"' && in_quotes == 1)
			|| (string[index] == 39 && in_dquotes == 1)
			|| string[index] != '"' && string[index] != 39)
		{
			string_token[ptr_index] = string[index];
			ptr_index ++;
		}
		index ++;
	}
	ft_printf("[%s] ", string);
	return (1);
}

/*
String_Tokenizer s'occupe de creer les tokens sur les chaines de characteres.
Une chaine de characetre est delimitee par un operateur logique, un whitespace
ou une parenthese.
La fonction n'enleve pas les doubles quotes et les singles quotes delimitant
les chaines.
Elle ajoute une nouvelle node a la liste t_list *tokens_list et lui donne
t_token *node en contenu. 
*/
static int	string_tokenizer(char *cmd_line, int *index, t_minishell *minishell)
{
	t_token	*node;
	int		in_quotes;
	int		in_dquotes;
	int		current;

	current = *index;
	in_quotes = 0;
	in_dquotes = 0;
	node = malloc(sizeof(t_token));
	if (!node)
		return (0);
	while (cmd_line[*index])
	{
		if (cmd_line[*index] == '"' || cmd_line[*index] == 39)
		{
			if (cmd_line[*index] == '"' && in_quotes == 0)
				in_dquotes = !in_dquotes;
			if (cmd_line[*index] == 39 && in_dquotes == 0)
				in_quotes = !in_quotes;
		}
		if (is_separator(cmd_line, *index) && in_quotes == 0 && in_dquotes == 0)
			break ;
		*index += 1;
	}
	node->token = ft_substr(cmd_line, current, (*index - current));
	if (!node->token)
		return (free(node), 0);
	node->type = STRING;
	ft_lstadd_back(&minishell->tokens_list, ft_lstnew(node));
	return (1);
}

/*
Operator_Tokenizer s'occupe de creer les tokens sur les operateurs logique ainsi
que sur les parentheses.
Elle ajoute une nouvelle node a la liste t_list *tokens_list et lui donne
t_token *node en contenu. 
*/
int	get_token_type(char *token)
{
	if (ft_strlen(token) == 2)
	{
		if (token[1] == '|')
			return (OR);
		else if (token[1] == '&')
			return (AND);
		else if (token[1] == '<')
			return (HERE_DOC);
		else
			return (APPEND);
	}
	else
	{
		if (token[0] == '|')
			return (PIPE);
		else if (token[0] == '(')
			return (OPEN_BRACKET);
		else if (token[0] == ')')
			return (CLOSE_BRACKET);
		else if (token[0] == '<')
			return (REDIR_IN);
		else
			return (REDIR_OUT);
	}
	return (TOKEN_ERROR);
}

int	operator_tokenizer(char *cmd_line, int *index, t_minishell *minishell)
{
	t_token	*node;
	int		ptr_token;

	ptr_token = 0;
	node = malloc(sizeof(t_token));
	if (!node)
		return (0);
	node->token = ft_calloc(sizeof(char), 3);
	if (!node->token)
		return (free(node), 0);
	node->token[ptr_token ++] = cmd_line[*index];
	*index += 1;
	if (cmd_line[*index] && (cmd_line[*index] == '&'
		|| cmd_line[*index] == '|')
		|| cmd_line[*index] == '>'
		|| cmd_line[*index] == '<')
	{
		node->token[ptr_token ++] = cmd_line[*index];
		*index += 1;
	}
	node->type = get_token_type(node->token);
	ft_lstadd_back(&minishell->tokens_list, ft_lstnew(node));
	return (1);
}

/*
Fonction d'entree du tokenizer
La fonction lit l'input du shell et creer des tokens en fonction des operateurs, 
des whites space ainsi que des chaines de characteres.
L'index est directement modifier par les fonctions qui creer les tokens.
Les fonctions renvoies 0 en cas d'erreurs d'allocations.
*/
int	tokenizer(char *cmd_line, t_minishell *minishell)
{
	int	index;

	index = 0;
	while (cmd_line[index])
	{
		if (cmd_line[index] == '"' || cmd_line[index] == 39
			|| !is_separator(cmd_line, index))
		{
			if (!string_tokenizer(cmd_line, &index, minishell))
				return (free_token_list(&minishell->tokens_list), 0);
		}
		else if (is_operator(cmd_line, index))
		{
			if (!operator_tokenizer(cmd_line, &index, minishell))
				return (free_token_list(&minishell->tokens_list), 0);
		}
		else
			index ++;
	}
	return (1);
}
