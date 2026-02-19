#include <minishell.h>

int is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4)
		return (1);
	if (ft_strncmp(args[0], "cd", 2) == 0 && ft_strlen(args[0]) == 2)
		return (1);
	if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
		return (1);
	if (ft_strncmp(args[0], "export", 6) == 0 && ft_strlen(args[0]) == 6)
		return (1);
	if (ft_strncmp(args[0], "unset", 5) == 0 && ft_strlen(args[0]) == 5)
		return (1);
	if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
		return (1);
	if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		return (1);
	return (0);
}