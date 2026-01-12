#include "minishell.h"

static char	*ft_strcat(char *dest, char *src)
{
	char	*tmp;

	if (!dest)
	{
		dest = ft_strdup(src);
		if (!dest)
			return (NULL);
		return (dest);
	}
	tmp = ft_strdup(dest);
	if (!tmp)
		return (NULL);
	free (dest);
	dest = ft_strjoin(tmp, src);
	free (tmp);
	return (dest);
}

void	free_tab(char **tab)
{
	int	index;

	index = 0;
	while (tab[index])
	{
		free (tab[index]);
		index ++;
	}
	free(tab);
}

static char	*get_path(char *cmd, char *envp_path)
{
	char	**splited_path;
	char	*cmd_path;
	int		index;

	index = 0;
	cmd_path = NULL;
	splited_path = ft_split(envp_path, ':');
	if (!splited_path)
		return (NULL);
	while (splited_path[index])
	{
		cmd_path = ft_strcat(cmd_path, splited_path[index]);
		cmd_path = ft_strcat(cmd_path, "/");
		cmd_path = ft_strcat(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_tab(splited_path);
			return (cmd_path);
		}
		free(cmd_path);
		cmd_path = NULL;
		index ++;
	}
	free_tab(splited_path);
	return (NULL);
}

char *find_command(t_ast *node, char *envp[])
{
	char	*cmd_path;
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			cmd_path = get_path(((t_token *)(node->lst_token->content))->literal, envp[index]);
			if (access(cmd_path, X_OK) == -1)
				return (free(cmd_path), NULL);
			return (cmd_path);
		}
		index ++;
	}
	return (NULL);
}
