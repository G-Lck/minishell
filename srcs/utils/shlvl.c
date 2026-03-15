/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glucken <glucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:00:00 by glucken           #+#    #+#             */
/*   Updated: 2026/03/11 14:00:00 by glucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_env **env)
{
	t_env	*var;
	int		level;
	char	*new_value;

	var = find_env_var(*env, "SHLVL");
	if (var)
	{
		level = ft_atoi(var->value) + 1;
		new_value = ft_itoa(level);
		free(var->value);
		var->value = new_value;
	}
	else
		add_env_var(env, "SHLVL", "1");
}
