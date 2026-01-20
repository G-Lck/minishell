#include "minishell.h"

char **tokens_to_args(t_list *token_list)
{
	t_list *current;
	t_token *token;
	char **args;
	int argc = 0;
	int i;

	if (!token_list)
		return (NULL);
	current = token_list;
	while (current)
	{
		argc++;
		current = current->next;
	}

	args = malloc(sizeof(char *) * (argc + 1));
	if (!args)
		return (NULL);
	current = token_list;
	i = 0;
	while (current && i < argc)
	{
		token = (t_token *)current->content;
		if (token && token->literal)
			args[i] = ft_strdup(token->literal);
		else
			args[i] = ft_strdup("");
		current = current->next;
		i++;
	}
	args[argc] = NULL;

	return (args);
}

void free_args(char **args)
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

void simple_command_exec(t_ast *node, t_minishell *data)
{
	char **args;
	int builtin_status;
	int status;
	char *cmd_path;
	int i;

	if (!node || !node->lst_token)
		exit(EXIT_FAILURE);

	args = tokens_to_args(node->lst_token);
	if (!args)
		exit(EXIT_FAILURE);

	ft_printf("EXEC: ");
	for (i = 0; args[i]; i++)
		ft_printf("%s ", args[i]);
	ft_printf("\n");

	builtin_status = is_builtin_and_execute(args, data);
	if (builtin_status != -1)
	{
		free_args(args);
		exit(builtin_status);
	}

	ft_printf("External command: %s\n", args[0]);
	cmd_path = find_command(node, &status, data->envp);

	if (status == OK)
	{
		ft_printf("Command found at: %s\n", cmd_path);
		if (execve(cmd_path, args, data->envp) == -1)
		{
			perror(args[0]);
			free_args(args);
			exit(126);
		}
	}
	else
	{
		if (execve(args[0], args, data->envp) == -1)
		{
			ft_printf("minishell: %s: command not found\n", args[0]);
			free_args(args);
			exit(127);
		}
	}
	free_args(args);
	exit(EXIT_SUCCESS);
}
