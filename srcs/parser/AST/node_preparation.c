/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_preparation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:35:07 by theo              #+#    #+#             */
/*   Updated: 2026/01/19 16:30:40 by thbouver         ###   ########.fr       */
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

int	count_exec_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count ++;
	return (count);
}

char **dup_tab(char **src, int size)
{
	char	**new_tab;
	int		index;

	index = 0;
	new_tab = ft_calloc(sizeof(char *), size + 1);
	if (!new_tab)
		return (NULL);
	while (src[index])
	{
		new_tab[index] = ft_strdup(src[index]);
		if (!new_tab[index])
			return (NULL);
		index ++;
	}
	return (new_tab);
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

int	create_command_node(t_token *token, t_ast *node, t_minishell *minishell)
{
	char	**tmp;
	int		index;

	index = 0;

	if (count_exec_tokens(node->exec_token) == 0)
	{
		free(node->exec_token);
		node->exec_token = ft_calloc(sizeof(char *), 2);
		node->exec_token[0] = get_token_literal(token->literal, minishell);
		return (1);
	}
	tmp = dup_tab(node->exec_token, count_exec_tokens(node->exec_token) + 1);
	if (!tmp)
		return (0);
	tmp[count_exec_tokens(node->exec_token)] = get_token_literal(token->literal, minishell);
	free_tab(node->exec_token);
	node->exec_token = dup_tab(tmp, count_exec_tokens(tmp));
	free_tab(tmp);
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
