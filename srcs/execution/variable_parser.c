/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*handle_special_var(char c)
{
	char	*temp;

	temp = malloc(sizeof(char) * 3);
	if (!temp)
		return (NULL);
	temp[0] = '$';
	temp[1] = c;
	temp[2] = '\0';
	return (temp);
}

static char	*handle_normal_var(char *str)
{
	int		i;
	char	*name;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 1)
		return (ft_strdup(""));
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i + 1);
	return (name);
}

char	*get_var_name(char *str)
{
	if (ft_strlen(str) == 1 || !(ft_isalpha(str[1]) || str[1] == '_'))
		return (ft_strdup("$"));
	if (str[1] == '$' || str[1] == '?' || ft_isdigit(str[1]))
		return (handle_special_var(str[1]));
	return (handle_normal_var(str));
}
