/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:54:56 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/12/02 10:45:52 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	overflow_return(int neg)
{
	if (neg == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] - '0' + res * 10 < res)
			return (overflow_return(neg));
		res = str[i] - '0' + res * 10;
		i++;
	}
	return ((int)res * neg);
}
