/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 11:24:58 by avan-ber       #+#    #+#                */
/*   Updated: 2019/11/14 20:16:28 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	calc_i(int n)
{
	int i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;

	i = calc_i(n);
	str = (char *)malloc(i + 1);
	if (!str)
		return (0);
	if (n < 0)
		str[0] = '-';
	str[i] = '\0';
	i--;
	if (n == 0)
		str[i] = '0';
	while (n != 0)
	{
		if (n > 0)
			str[i] = '0' + n % 10;
		else
			str[i] = '0' - (n % 10);
		n /= 10;
		i--;
	}
	return (str);
}
