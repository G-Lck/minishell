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

void	fill_token_tab(t_token *token_tab, char *expanded_token)
{
	int	index;
	int	token_tab_index;

	index = 0;
	token_tab_index = 0;
	while (expanded_token[index])
	{
		if (expanded_token[index] == '"' || expanded_token[index] == '\''
				|| expanded_token[index])
		{
			create_token_literal(&token_tab[token_tab_index], expanded_token, &index);
			token_tab_index ++;
		}
		index ++;
	}
}

int	token_counter(char *expanded_token)
{
	int	count;
	int	index;
	int	in_quote;
	int	in_dquote;

	count = 1;
	index = 0;
	in_quote = 0;
	in_dquote = 0;
	while (expanded_token[index])
	{
		if (expanded_token[index] == '"' && in_quote == 0)
			in_dquote = !in_dquote;
		if (expanded_token[index] == 39 && in_dquote == 0)
			in_quote = !in_quote;
		if ((in_quote != 1 || in_dquote != 1) && is_wspace(expanded_token[index]))
			count ++;
		index ++;
	}
	return (count);
}

t_token	*split_expension(char *literal, int *token_count, t_minishell *minishell)
{
	t_token	*token_tab;
	int		index;
	char	*expanded_token;

	index = 0;
	expanded_token = expand_variables(literal, minishell);
	*token_count = token_counter(expanded_token);
	token_tab = ft_calloc(sizeof(t_token), *token_count);
	if (!token_tab)
		return (NULL);
	fill_token_tab(token_tab, expanded_token);
	return (token_tab);
}
