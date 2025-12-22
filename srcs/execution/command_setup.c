#include "minishell.h"

int	parse_redir(t_ast *node, t_list *token_lst)
{
	t_token	*token_tmp;
	t_redir	*new_redir;
	t_list	*new_node;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);
	token_tmp = token_lst->content;
	new_redir->redir_type = token_tmp->type;
	token_tmp = token_lst->next->content;
	new_redir->target = ft_strdup("test");
	new_node = ft_lstnew(new_redir);
	if (!new_node)
		return (0);
	ft_lstadd_back(&node->redirs, new_node);
}

int	prepare_node(t_ast *node)
{
	int		index;
	t_list	*lst_tmp;
	t_token *current_token;

	index = 0;
	lst_tmp = node->lst_token;
	while (index < node->lst_len)
	{
		current_token = lst_tmp->content;
		if (current_token->type == REDIR_IN || current_token->type == REDIR_OUT
			|| current_token->type == APPEND
			|| current_token->type == HERE_DOC)
		parse_redir(node, lst_tmp);
			lst_tmp = lst_tmp->next;
		index ++;
	}
	t_list *redir_tmp = node->redirs;
	while (redir_tmp && redir_tmp->next)
	{
		t_redir *crt = redir_tmp->content;
		ft_printf("Redir -> %s", crt->target);
		redir_tmp = redir_tmp->next;
	}
	ft_printf("\n");
	return (1);
}

void	commands_setup(t_ast *node)
{
	if (node->node_type == AND_OP || node->node_type == OR_OP || node->node_type == PIPE_OP)
		commands_setup (node->next_left);
	else
	{
		prepare_node(node);
		return ;
	}
	commands_setup(node->next_right);
}
