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

static int	cd_to_path(char *path, t_env **env, t_minishell *minishell)
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
	set_env_var(env, "OLDPWD", old_pwd);
	free(old_pwd);
	set_env_var(env, "PWD", new_pwd);
	free(minishell->current_dir);
	minishell->current_dir = ft_strdup(new_pwd);
	free(new_pwd);
	return (0);
}

int	ft_cd(char **args, t_env **env, t_minishell *minishell)
{
	char	*path;
	t_env	*home;

	if (!args)
		return (1);
	else if (args[0] && !args[1])
	{
		home = find_env_var(*env, "HOME");
		if (!home)
			return (ft_fprintf(2, "minishell: cd: HOME not set\n"), 1);
		path = home->value;
	}
	else if (args[2])
		return (ft_fprintf(2, "minishell: cd: too many arguments\n"), 1);
	else
		path = args[1];
	return (cd_to_path(path, env, minishell));
}
