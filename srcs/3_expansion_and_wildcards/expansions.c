/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:07 by theo              #+#    #+#             */
/*   Updated: 2026/03/05 23:17:55 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_token_literal(t_token *token_tab, char *str, int *index)
{
	int		in_quotes;
	int		in_dquotes;
	int		current;

	current = *index;
	in_quotes = 0;
	in_dquotes = 0;
	while (str[*index])
	{
		if (str[*index] == '"' || str[*index] == 39)
		{
			if (str[*index] == '"' && in_quotes == 0)
				in_dquotes = !in_dquotes;
			if (str[*index] == 39 && in_dquotes == 0)
				in_quotes = !in_quotes;
		}
		if (is_separator(str, *index) && in_quotes == 0 && in_dquotes == 0)
			break ;
		*index += 1;
	}
	token_tab->literal = ft_substr(str, current, (*index - current));
	token_tab->literal = string_cleaner(token_tab->literal);
	if (!token_tab)
		return (0);
	return (1);
}

void	fill_token_tab(t_token *t_tab, char *expanded_token, int token_count)
{
	int	i;
	int	token_tab_index;

	i = 0;
	token_tab_index = 0;
	while (i < token_count)
	{
		if (expanded_token[i] == '"' || expanded_token[i] == '\''
			|| expanded_token[i])
		{
			create_token_literal(&t_tab[token_tab_index], expanded_token, &i);
			token_tab_index ++;
		}
		i ++;
	}
}

int	token_counter(char *expanded_token)
{
	int	count;
	int	i;
	int	in_quote;
	int	in_dquote;

	count = 1;
	i = 0;
	in_quote = 0;
	in_dquote = 0;
	while (expanded_token[i])
	{
		if (expanded_token[i] == '"' && in_quote == 0)
			in_dquote = !in_dquote;
		if (expanded_token[i] == 39 && in_dquote == 0)
			in_quote = !in_quote;
		if ((in_quote != 1 || in_dquote != 1) && is_wspace(expanded_token[i]))
			count ++;
		i ++;
	}
	return (count);
}
