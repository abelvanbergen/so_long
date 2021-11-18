/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 11:30:08 by avan-ber       #+#    #+#                */
/*   Updated: 2019/11/12 15:25:25 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *l;

	l = *alst;
	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	while (l->next != 0)
		l = l->next;
	l->next = new;
}
