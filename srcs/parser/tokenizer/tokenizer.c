/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:08:35 by theo              #+#    #+#             */
/*   Updated: 2025/12/10 14:58:51 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Fonction inutile pour le moment.
Permet de supprimer les doubles quotes et singles quotes de delimation tout
en preservant ceux a afficher
*/
static int	string_cleaner(char *string, t_minishell *minishell)
{
	char	*tmp;
	int		in_quotes;
	int		in_dquotes;
	int		index;
	int		ptr_index;

	ptr_index = 0;
	index = 0;
	in_dquotes = 0;
	in_quotes = 0;
	tmp = ft_calloc(sizeof(char), ft_strlen(string + 1));
	if (!tmp)
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
			tmp[ptr_index] = string[index];
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
static int	string_tokenizer(char *cmd_line, int *index, t_minishell *minishell, int current_token_index)
{
	char	*tmp;
	int		in_quotes;
	int		in_dquotes;
	int		current;

	current = *index;
	in_quotes = 0;
	in_dquotes = 0;
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
	tmp = ft_substr(cmd_line, current, (*index - current));
	if (!tmp)
		return (0);
	if (!create_token(tmp, STRING, current_token_index, minishell))
		return (free(tmp), 0);
	return (free(tmp), 1);
}

/*
Operator_Tokenizer s'occupe de creer les tokens sur les operateurs logique ainsi
que sur les parentheses.
Elle ajoute une nouvelle node a la liste t_list *tokens_list et lui donne
t_token *node en contenu. 
*/
static int	operator_tokenizer(char *cmd_line, int *index, t_minishell *minishell, int current_token_index)
{
	char	*tmp;
	int		ptr_index;

	ptr_index = 0;
	tmp = ft_calloc(sizeof(char), 3);
	if (!tmp)
		return (0);
	tmp[ptr_index ++] = cmd_line[*index];
	*index += 1;
	if (cmd_line[*index] && (cmd_line[*index] == '&'
		|| cmd_line[*index] == '|')
		|| cmd_line[*index] == '>'
		|| cmd_line[*index] == '<')
	{
		tmp[ptr_index ++] = cmd_line[*index];
		*index += 1;
	}
	if (!create_token(tmp, get_token_type(tmp), current_token_index, minishell))
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
int	tokenizer(char *cmd_line, t_minishell *minishell)
{
	int	current_token_index;
	int	index;

	current_token_index = 0;
	index = 0;
	while (cmd_line[index])
	{
		if (cmd_line[index] == '"' || cmd_line[index] == 39
			|| !is_separator(cmd_line, index))
		{
			if (!string_tokenizer(cmd_line, &index, minishell, current_token_index ++))
				return (free_token_list(&minishell->tokens_list), 0);
		}
		else if (is_operator(cmd_line, index))
		{
			if (!operator_tokenizer(cmd_line, &index, minishell, current_token_index ++))
				return (free_token_list(&minishell->tokens_list), 0);
		}
		else
			index ++;
	}
	return (1);
}
