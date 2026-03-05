/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 

void	init_minishell(t_minishell *minishell, char *envp[])
{
	minishell->tokens_list = NULL;
	minishell->ast = NULL;
	minishell->input = NULL;
	minishell->envp = envp;
	minishell->env = NULL;
	minishell->current_dir = ft_calloc(sizeof(char), 100);
	minishell->exit_code = 0;
	minishell->last_status = 0;
	getcwd(minishell->current_dir, 100);
	minishell->previous_last_status = 0;
}