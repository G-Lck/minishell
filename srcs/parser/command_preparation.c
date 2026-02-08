/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_preparation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:35:07 by theo              #+#    #+#             */
/*   Updated: 2026/02/08 15:30:11 by glucken          ###   ########.fr       */
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
		expanded_var = expand_variables(target, minishell);
		if (expanded_var != NULL && check_wspaces(expanded_var))
			ft_printf("ambiguous redirection\n");
		new_node = new_redir_node(expanded_var, type);
		ft_lstadd_back(&node->redirs, new_node);
	}
	return (1);
}

int	create_command_node(t_token *token, t_ast *node, t_minishell *minishell)
{
	char	*cleaned_string;
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
		index = 0;
		while (index < token_count)
		{
			free(token_tab[index].literal);
			index ++;
		}
		free (token_tab);
	}
	else if (need_to_glob(token->literal))
	{
		index = 0;
		char	**tab;

		cleaned_string = ft_strdup(token->literal);
		cleaned_string = string_cleaner(cleaned_string);
		tab = wildcards_parser(cleaned_string, minishell);
		while (tab[index])
		{
			new_node = new_exec_node(tab[index], token->type);
			ft_lstadd_back(&node->exec_lst, new_node);
			index ++;
		}
		free(cleaned_string);
		free_tab(tab);
	}
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
