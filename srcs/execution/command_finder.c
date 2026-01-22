#include "minishell.h"

int	is_dir(char *path)
{
	char	buff[1];
	int		fd;

	fd = open(path, O_RDONLY);
	if (!fd)
		return (0);
	if (read(fd, buff, 1) == -1 && errno == EISDIR)
		return (close(fd), 1);
	return (close(fd), 0);
}

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

char *find_command(t_ast *node, int *status, char **envp)
{
	char	*cmd_path;
	int		index;

	index = 0;
	if (access(node->exec_token[0], F_OK) == 0)
	{
		if (is_dir(node->exec_token[0]) == 1 && node->exec_token[0][0] == '.' && node->exec_token[0][0] == '/')
			return (*status = IS_DIRECTORY, NULL);
		if (is_dir(node->exec_token[0]) == 1)
			return (*status = IS_DIRECTORY, NULL);
		if (access(node->exec_token[0], X_OK) == -1)
			return (*status = PERMISSION_DENIED, NULL);
		return (*status = OK, node->exec_token[0]);
	}
	while (envp[index])
	{		
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			ft_printf("index: %i\n", index);
			cmd_path = get_path(node->exec_token[0], envp[index]);
			if (cmd_path)
			{
				if (access(cmd_path, X_OK) == -1)
					return (free(cmd_path), *status = PERMISSION_DENIED, NULL);
				else
					return (*status = OK, cmd_path);
			}
			break;
		}
		
		index++;
	}
	return (*status = COMMAND_NOT_FOUND, NULL);
}
