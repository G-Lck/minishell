/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_preparation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:35:07 by theo              #+#    #+#             */
/*   Updated: 2026/01/26 13:58:11 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_redir_node(char *target, t_token_type type)
{
	t_list	*new_node;
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->redir_type = type;
	new_redir->target = ft_strdup(target);
	if (!new_redir->target)
		return(NULL);
	new_node = ft_lstnew(new_redir);
	return (new_node);
}

t_list	*new_exec_node(char *token_literal, t_token_type type)
{
	t_list	*new_node;
	t_token	*new_exec_token;

	new_exec_token = malloc(sizeof(t_token));
	if (!new_exec_token)
		return (NULL);
	new_exec_token->type = type;
	new_exec_token->literal = ft_strdup(token_literal);
	if (!new_exec_token->literal)
		return(NULL);
	new_node = ft_lstnew(new_exec_token);
	return (new_node);
}

int	check_wspaces(char *str)
{
	int	index;

	index = 0;
	while(str[index])
	{
		if ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
			return (1);
		index ++;
	}
	return (0);
}

int	create_redir_node(char *target, t_token_type type, t_ast *node, t_minishell *minishell)
{
	t_list	*new_node;
	char	*expanded_var;

	if (target[0] != '$')
	{
		new_node = new_redir_node(target, type);
		if (!new_node)
			return (0);
		ft_lstadd_back(&node->redirs, new_node);
	}
	else
	{
		expanded_var = expand_variables(target, minishell->env);
		if (expanded_var != NULL && check_wspaces(expanded_var))
			ft_printf("ambiguous redirection\n");
		new_node = new_redir_node(expanded_var, type);
		ft_lstadd_back(&node->redirs, new_node);
	}
	return (1);
}

char	*get_token_literal(char *token_literal, t_minishell *minishell)
{
	char	*new_token_literal;

	if (ft_strchr(token_literal, '$') == NULL)
	{
		new_token_literal = ft_strdup(token_literal);
		if (!new_token_literal)
			return (NULL);
		return (new_token_literal);
	}
	else
	{
		new_token_literal = expand_variables(token_literal, minishell->env);
		if (ft_strlen(new_token_literal) == 0)
			new_token_literal = ft_strdup(token_literal);
		return (new_token_literal);
	}
	return (NULL);
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

t_token	*split_expension(char *literal, int *token_count, t_minishell *minishell)
{
	t_token	*token_tab;
	int		index;
	char	*expanded_token;

	index = 0;
	expanded_token = expand_variables(literal, minishell->env);
	*token_count = token_counter(expanded_token);
	token_tab = ft_calloc(sizeof(t_token), *token_count);
	if (!token_tab)
		return (NULL);
	fill_token_tab(token_tab, expanded_token);
	return (token_tab);
}

int	create_command_node(t_token *token, t_ast *node, t_minishell *minishell)
{
	int		token_count;
	int		index;
	t_list	*new_node;
	t_token	*token_tab;

	index = 0;
	if (ft_strchr(token->literal, '$') != NULL)
	{
		token_tab = split_expension(token->literal, &token_count, minishell);
		while (index < token_count)
		{
			new_node = new_exec_node(token_tab[index].literal, STRING);
			ft_lstadd_back(&node->exec_lst, new_node);
			index ++;
		}
	}
	else if (token->literal[0] == '*')
	{
		//wildcards parser
	}
	else
	{
		new_node = new_exec_node(token->literal, token->type);
		ft_lstadd_back(&node->exec_lst, new_node);
	}
	return (1);
}

int	node_preparation(t_ast *node, t_minishell *minishell)
{
	int	index = 0;
	t_token *token;
	t_token *tmp;

	while (index < node->lst_len)
	{
		token = node->lst_token->content;
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == HERE_DOC || token->type == APPEND)
		{
			tmp = node->lst_token->next->content;
			create_redir_node(tmp->literal, token->type, node, minishell);
			node->lst_token = node->lst_token->next;
			index ++;
		}
		else
			create_command_node(token, node, minishell);
		node->lst_token = node->lst_token->next;
		index ++;
	}
	return (0);
}
