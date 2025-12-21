#include "minishell.h"
#include "builtins.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
int	ft_exit(t_list *args, t_minishell *minishell)
{
	t_token *arg;

	if (!args)
	{
		minishell->exit_code = minishell->last_status;
		return (EXIT_SHELL);
	}
	arg = args->content;
	if (!ft_isnumber(arg->literal))
	{
		ft_fprintf(2, "exit: numeric argument required\n");
		minishell->exit_code = 255;
	} else if (args->next)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		return (1);
	} else
		minishell->exit_code = ft_atoi(arg->literal) % 256;
	return (EXIT_SHELL);
}
