/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:07 by theo              #+#    #+#             */
/*   Updated: 2026/03/05 23:18:37 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_wildcards(char *pat)
{
	int	index;

	index = 0;
	while (pat[index])
	{
		if (pat[index] != '*')
			return (0);
		index ++;
	}
	return (0);
}

int	pattern_checker(char *ref, char *pat, int n, int m)
{
	int	index;

	if (m == 0)
		return (n == 0);
	index = 0;
	if (n == 0)
	{
		while (index < m)
		{
			if (pat[index] != '*')
				return (0);
			index++;
		}
		return (1);
	}
	if (ref[n - 1] == pat[m - 1])
		return (pattern_checker(ref, pat, n - 1, m - 1));
	if (pat[m - 1] == '*')
		return (pattern_checker(ref, pat, n, m - 1)
			|| pattern_checker(ref, pat, n - 1, m));
	return (0);
}

int	get_tab_size(char *pattern, t_minishell *minishell)
{
	struct dirent	*dent;
	int				count;
	DIR				*dir;

	count = 0;
	dir = opendir(minishell->current_dir);
	dent = readdir(dir);
	while (dent != NULL)
	{
		if (is_only_wildcards(pattern))
			count ++;
		else if (dent->d_name[0] != '.'
			&& pattern_checker(dent->d_name, pattern,
				ft_strlen(dent->d_name), ft_strlen(pattern)))
			count ++;
		dent = readdir(dir);
	}
	closedir(dir);
	return (count);
}

int	need_to_glob(char *token_literal)
{
	int	in_dquotes;
	int	in_quotes;
	int	index;

	in_dquotes = 0;
	in_quotes = 0;
	index = 0;
	while (token_literal[index])
	{
		if (token_literal[index] == '"' && in_quotes == 0)
			in_dquotes = !in_dquotes;
		if (token_literal[index] == 39 && in_dquotes == 0)
			in_quotes = !in_quotes;
		if (in_quotes == 0 && in_dquotes == 0 && token_literal[index] == '*')
			return (1);
		index ++;
	}
	return (0);
}

char	**wildcards_parser(char *pattern, t_minishell *minishell)
{
	struct dirent	*dent;
	int				index;
	int				tab_size;
	char			**results;
	DIR				*dir;

	index = 0;
	tab_size = get_tab_size(pattern, minishell);
	results = ft_calloc(sizeof(char *), get_tab_size(pattern, minishell) + 1);
	if (tab_size == 0)
		return (results[0] = ft_strdup(pattern), results);
	dir = opendir(minishell->current_dir);
	dent = readdir(dir);
	while (dent != NULL)
	{
		if (is_only_wildcards(pattern))
			results[index ++] = ft_strdup(dent->d_name);
		else if (dent->d_name[0] != '.'
			&& pattern_checker(dent->d_name, pattern,
				ft_strlen(dent->d_name), ft_strlen(pattern)))
			results[index ++] = ft_strdup(dent->d_name);
		dent = readdir(dir);
	}
	closedir(dir);
	return (results);
}
