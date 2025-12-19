#include "minishell.h"

int	exec_ast(t_ast *node);

int exec_cmd(t_ast *node)
{
	t_list	*lst_token;
	t_token	*token;
	int		i;

	ft_printf("cmd: ");
	lst_token = node->lst_token;
	i = 0;
	while (i < node->lst_len)
	{
		token = lst_token->content;
		ft_printf(token->literal);
		lst_token = lst_token->next;
		i++;
	}
	ft_printf("\n");
	return (1);

}

int	exec_pipe_node(t_ast *node)
{
	ft_printf("to a pipe\n");
	return (1);
}

int	exec_ast(t_ast *node);

int	exec_in_subshell(t_ast *node)
{
	ft_printf("in subshell\n");
	return (exec_ast(node));
}


int	exec_ast(t_ast *node)
{
	if (!node)
		return (0);

	if (node->is_subshell == true)
	{
		node->is_subshell = false;
		return(exec_in_subshell(node));
	}
	if (node->node_type == PIPE_OP)
		return (exec_pipe_node(node));
	if (node->node_type == AND_OP && exec_ast(node->next_left))
		return (exec_ast(node->next_right));
	if (node->node_type == OR_OP && !exec_ast(node->next_left))
		return (exec_ast(node->next_right));
	return (exec_cmd(node));
}
