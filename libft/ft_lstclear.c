/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:19:56 by theo              #+#    #+#             */
/*   Updated: 2025/08/03 11:53:39 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*saved;

	tmp = *lst;
	while (tmp)
	{
		saved = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = saved;
	}
	*lst = NULL;
}
