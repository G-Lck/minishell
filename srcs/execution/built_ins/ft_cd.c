/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:00:00 by garance          #+#    #+#             */
/*   Updated: 2025/01/13 09:00:00 by garance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_dir(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		free(cwd);
		return (NULL);
	}
	return (cwd);
}

static int	cd_to_path(char *path, t_env **env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_current_dir();
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	new_pwd = get_current_dir();
	if (!new_pwd)
	{
		free(old_pwd);
		return (1);
	}
	if (old_pwd)
	{
		set_env_var(env, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	set_env_var(env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	if (!args || !args[0])
	{
		ft_fprintf(2, "minishell: cd: missing argument\n");
		return (1);
	}
	if (args[1])
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	return (cd_to_path(args[0], env));
}
