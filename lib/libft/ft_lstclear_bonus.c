/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 12:24:17 by avan-ber       #+#    #+#                */
/*   Updated: 2019/11/11 14:15:20 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*next;

	if (lst == 0)
		return ;
	list = *lst;
	while (list)
	{
		next = list->next;
		del(list->content);
		free(list);
		list = next;
	}
	*lst = 0;
}
