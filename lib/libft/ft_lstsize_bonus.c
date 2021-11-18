/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 11:16:28 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/18 20:00:08 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int c;

	if (lst == NULL)
		return (0);
	c = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		c++;
	}
	return (c);
}
