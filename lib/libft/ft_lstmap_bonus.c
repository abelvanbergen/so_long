/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 14:30:07 by avan-ber       #+#    #+#                */
/*   Updated: 2019/11/12 15:18:48 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*res;

	res = 0;
	if (lst == 0)
		return (0);
	while (lst != 0)
	{
		new = ft_lstnew(f(lst->content));
		if (new == 0)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
