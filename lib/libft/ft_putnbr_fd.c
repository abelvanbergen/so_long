/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 12:30:45 by avan-ber       #+#    #+#                */
/*   Updated: 2019/11/18 10:19:02 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr2_fd(int nb, int fd)
{
	if (nb < -9 || nb > 9)
		ft_putnbr2_fd(nb / 10, fd);
	if (nb >= 0)
		ft_putchar_fd('0' + nb % 10, fd);
	else
		ft_putchar_fd('0' - nb % 10, fd);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
		ft_putchar_fd('-', fd);
	ft_putnbr2_fd(nb, fd);
}
