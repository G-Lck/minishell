/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_preparation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:35:07 by theo              #+#    #+#             */
/*   Updated: 2026/03/05 23:16:14 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_redirs(char *f, t_token_type type, t_ast *n, t_minishell *m)
{
	t_list	*new_node;
	char	*expvar;

	if (f[0] != '$')
	{
		new_node = new_redir_node(f, type);
		if (!new_node)
			return (0);
	}
	else
	{
		if (ft_strlen(f) == 1)
		{
			new_node = new_redir_node("$", type);
			return (ft_lstadd_back(&n->redirs, new_node), 1);
		}
		expvar = expand_variables(f, m);
		if (ft_strlen(expvar) == 0 || (expvar != NULL && check_wspaces(expvar)))
			n->skip = true;
		new_node = new_redir_node(expvar, type);
	}
	ft_lstadd_back(&n->redirs, new_node);
	if (n->skip == true)
		ft_printf("ambiguous redirection\n");
	return (free (expvar), 1);
}

static void	create_expanded_command_node(t_token *t, t_ast *n, t_minishell *m)
{
	int		index;
	t_list	*new_node;
	char	**token_tab;
	char	*expanded_token;

	index = 0;
	expanded_token = expand_variables(t->literal, m);
	token_tab = ft_split(expanded_token, "\t\n\v\f\r ");
	while (token_tab[index])
	{
		new_node = new_exec_node(token_tab[index], STRING);
		ft_lstadd_back(&n->exec_lst, new_node);
		index ++;
	}
	free(expanded_token);
	free_tab(token_tab);
}

static void	create_wildcards_node(t_token *token, t_ast *node, t_minishell *m)
{
	int		index;
	char	*cleaned_string;
	char	**tab;
	t_list	*new_node;

	index = 0;
	cleaned_string = ft_strdup(token->literal);
	cleaned_string = string_cleaner(cleaned_string);
	tab = wildcards_parser(cleaned_string, m);
	while (tab[index])
	{
		new_node = new_exec_node(tab[index], token->type);
		ft_lstadd_back(&node->exec_lst, new_node);
		index ++;
	}
	free(cleaned_string);
	free_tab(tab);
}

int	create_command_node(t_token *token, t_ast *node, t_minishell *minishell)
{
	char	*cleaned_string;
	t_list	*new_node;

	if (ft_strchr(token->literal, '$') != NULL)
		create_expanded_command_node(token, node, minishell);
	else if (need_to_glob(token->literal))
		create_wildcards_node(token, node, minishell);
	else
	{
		cleaned_string = ft_strdup(token->literal);
		cleaned_string = string_cleaner(cleaned_string);
		if (!cleaned_string)
			return (0);
		new_node = new_exec_node(cleaned_string, token->type);
		free(cleaned_string);
		ft_lstadd_back(&node->exec_lst, new_node);
	}
	return (1);
}

int	command_preparation(t_ast *node, t_minishell *minishell)
{
	int		index;
	t_token	*token;
	t_token	*tmp;

	index = 0;
	while (index < node->lst_len)
	{
		token = node->lst_token->content;
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == HERE_DOC || token->type == APPEND)
		{
			tmp = node->lst_token->next->content;
			create_redirs(tmp->literal, token->type, node, minishell);
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
