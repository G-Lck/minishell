#include "minishell.h"


static void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int is_builtin_and_execute(char **args, t_minishell *minishell)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4)
		return (ft_echo(args, minishell->env));
	if (ft_strncmp(args[0], "cd", 2) == 0 && ft_strlen(args[0]) == 2)
		return (ft_cd(args, &minishell->env));
	if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
		return (ft_pwd());
	if (ft_strncmp(args[0], "export", 6) == 0 && ft_strlen(args[0]) == 6)
		return (ft_export(args, &minishell->env));
	if (ft_strncmp(args[0], "unset", 5) == 0 && ft_strlen(args[0]) == 5)
		return (ft_unset(args, &minishell->env));
	if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
		return (ft_env(minishell->env));
	if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		return (ft_exit(args, minishell));
	return (-1);
}

void exec_node(t_ast *node, t_minishell *minishell)
{
	char **args;
	int builtin_status;
	int status;
	char *cmd_path;
	int i;

	args = node->exec_token;
	if (!node || !node->exec_token)
		exit(EXIT_FAILURE);
	if (!args)
		exit(EXIT_FAILURE);

	builtin_status = is_builtin_and_execute(args, minishell);
	if (builtin_status != -1)
	{
		free_args(args);
		node->exec_status = builtin_status;
		return ;
	}
	ft_printf("External command: %s\n", args[0]);
	exec_executable(node, minishell);
	//print_token(node->lst_token);

	return ;
}
